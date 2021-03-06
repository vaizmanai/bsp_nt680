//This source code is generated by UI Designer Studio.
#include "UIFramework.h"
#include "UIFrameworkExt.h"
#include "UIGraphics.h"
#include "NVTToolCommand.h"
#include "UIMovieMapping.h"
#include "SysCommon.h"
#include "AppCommon.h"
#include "PrjCfg.h"
#include "WifiAppCmd.h"
#include "UIAppMoviePlay.h"
#include "UIAppMovie.h"
#include "UIFlowMovieFuncs.h"
#include "md_api.h"
//#NT#2016/05/31#Ben Wang -begin
//#NT#Add UVC multimedia function.
#if(UVC_MULTIMEDIA_FUNC == ENABLE)
#include "ImageApp_UsbMovie.h"
#endif
//#NT#2016/05/31#Ben Wang -end
#if (MOVIE_MAPPING_MULTIREC	== ENABLE)
#include "ImageApp_MovieMulti.h"
#endif
#if(WIFI_AP_FUNC==ENABLE)
#include "RtspNvtApi.h"
#endif
#include "UIAppWiFiCmd.h"
#include "WifiAppCmd.h"
#include "ImageApp_Movie.h"
#include "NMediaRecVdoEncAPI.h"

///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          UIAppWiFiCmdMovie
#define __DBGLVL__          6 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include "DebugModule.h"
//----------------------------------------------------------------------------
#if (WIFI_AP_FUNC==ENABLE)
static UINT32  gUIMenuWndWiFiMotionDetTimerID = NULL_TIMER;

//#NT#2017/01/03#Isiah Chang -begin
//#NT#Add WiFiCmd Bitrate control.
static BOOL   g_BRCAutoRun = FALSE;
static UINT32 g_BRCUpperBound = 0, g_BRCLowerBound = 0;
static INT32 g_BRCTotalLevel = 0, g_BRCCurrentLevel = 0;
//#NT#2017/01/03#Isiah Chang -end

void FlowWiFiMovie_StartRec(void)
{
	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_REC_START, 0);
}

void FlowWiFiMovie_StopRec(void)
{
	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_REC_STOP, 0);
}

void FlowWiFiMovie_StartLview(void)
{
	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_STRM_START, 0);
}
void FlowWiFiMovie_Stop2Idle(void)
{
//#NT#2016/05/31#Ben Wang -begin
//#NT#Add UVC multimedia function.
#if(UVC_MULTIMEDIA_FUNC == ENABLE)
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_UVC) {
		ImageApp_UsbMovie_LviewStop();
	} else
#endif
	{
    	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_REC_STOP, 0);
    	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_STRM_STOP, 0);
	}
//#NT#2016/05/31#Ben Wang -end
}
void WiFiCmd_MotionDetectStart(void)
{
	if (gUIMenuWndWiFiMotionDetTimerID == NULL_TIMER) {
		gUIMenuWndWiFiMotionDetTimerID = GxTimer_StartTimer(TIMER_HALF_SEC, NVTEVT_05SEC_TIMER, CONTINUE);
	}
}
void WiFiCmd_MotionDetectStop(void)
{
	if (gUIMenuWndWiFiMotionDetTimerID != NULL_TIMER) {
		GxTimer_StopTimer(&gUIMenuWndWiFiMotionDetTimerID);
	}

}

void WiFiCmd_OnMotionDetect(void)
{
	// Motion Detect function
	if (SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_ON && System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE) {
		static UINT32  uiMotionDetGo = 0;
		static UINT32  uiMotionDetStop = 0;

		//#NT#2016/10/18#Jeah Yen -begin
		//#NT#move code to support sensor map
		static UINT32  uiMotionDetRet = 0;
		Ux_SendEvent(0, NVTEVT_EXE_MOTION_DET_RUN, 1, (UINT32)&uiMotionDetRet);
		if (uiMotionDetRet == TRUE)
			//#NT#2016/10/18#Jeah Yen -end
		{
			uiMotionDetGo++;
			if (uiMotionDetGo >= 2) {
				uiMotionDetStop = 0;
				if (WiFiCmd_GetStatus() == WIFI_MOV_ST_LVIEW) {
					debug_msg("^GStart Record\r\n");
					// reset uiMotionDetGo
					uiMotionDetGo = 0;
                    //#NT#2017/05/24#Isiah Chang -begin
                    // Send socket to notify APP movie recording is started.
                    // Post event to record video and send socket to notify APP recording is started.
                    Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 2, 1, 1);
                    //#NT#2017/05/24#Isiah Chang -end
				}
			}
		} else {
			uiMotionDetStop++;
			if (uiMotionDetStop >= 2) { // 1 sec
				uiMotionDetGo = 0;
			}
			if (uiMotionDetStop >= 20) // 10 Sec
			{
				uiMotionDetStop = 0;
				if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD) {
					if (FlowMovie_GetRecCurrTime() >= 1 || (SysGetFlag(FL_MOVIE_TIMELAPSE_REC) != MOVIE_TIMELAPSEREC_OFF)) {
                        //#NT#2017/05/24#Isiah Chang -begin
                        // Send socket to notify APP movie recording is started.
                        debug_msg("^RWIFIAPP_RET_RECORD_STOPPED\r\n");
                        // Post event to record video and send socket to notify APP recording is started.
                        Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 2, 0, 1);
                        //#NT#2017/05/24#Isiah Chang -end
					}
				}
			}
		}
	}
}
INT32 WiFiCmd_OnExeMovieRec(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	BOOL startRec = 0;
	UINT32 uiNotifyAPPStatus = 0;
	UINT32 result = WIFIAPP_RET_OK;
	UINT32 curStatus = 0;
//#NT#2016/08/31#Isiah Chang -begin
//#NT#Parameter number must be larger then 0. Fixed mantis bug id:0107729
	if (paramNum > 0) {
		startRec = paramArray[0];

		if (paramNum > 1) {
			uiNotifyAPPStatus = paramArray[1];
		}
	} else {
		WifiCmd_Done(WIFIFLAG_RECORD_DONE, WIFIAPP_RET_PAR_ERR);
		DBG_ERR("too few parameter!\r\n");
		return NVTEVT_CONSUME;
	}
//#NT#2016/08/31#Isiah Chang -end
	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		WifiCmd_Done(WIFIFLAG_RECORD_DONE, WIFIAPP_RET_STATE_ERR);
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	curStatus = WiFiCmd_GetStatus();
	if (startRec) {
		if (curStatus == WIFI_MOV_ST_LVIEW) {
			UINT32 MaxTime = MovieExe_GetFreeRecSec();
			if ((MaxTime <= 3) && (SysGetFlag(FL_MOVIE_CYCLIC_REC) == MOVIE_CYCLICREC_OFF)) {
				result = WIFIAPP_RET_STORAGE_FULL;
				DBG_ERR("recTime<3 sec\r\n");
			} else {
                // Reset Current record time
                FlowMovie_SetRecCurrTime(0);

                //#NT#2017/05/24#Isiah Chang -begin
                // Send socket to notify APP movie recording is started.
                #if 0
                // Send socket to notify APP movie recording is started.
                if(uiNotifyAPPStatus)
                {
                    WifiApp_SendCmd(WIFIAPP_CMD_NOTIFY_STATUS, WIFIAPP_RET_RECORD_STARTED);
                }
                else
                #endif
                {
                    FlowWiFiMovie_StartRec();
                    if(SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_ON && uiNotifyAPPStatus)
                    {
                        WifiApp_SendCmd(WIFIAPP_CMD_NOTIFY_STATUS, WIFIAPP_RET_RECORD_STARTED);
                    }
                }
                //#NT#2017/05/24#Isiah Chang -end
            }
		} else if (curStatus == WIFI_MOV_ST_IDLE) {
			result = WIFIAPP_RET_FAIL;
			DBG_ERR("idle state,cannot record\r\n");
		}
	} else { //stop rec

		UINT32 recordTime = FlowMovie_GetRecCurrTime();

		if ((curStatus == WIFI_MOV_ST_RECORD) && ((recordTime >= 1) || (SysGetFlag(FL_MOVIE_TIMELAPSE_REC) != MOVIE_TIMELAPSEREC_OFF))) {
			FlowWiFiMovie_StopRec();
			// Notify Maximum Record Time
			UI_SetData(FL_WIFI_MOVIE_MAXRECTIME, MovieExe_GetMaxRecSec());
            //#NT#2017/05/24#Isiah Chang -begin
            // Send socket to notify APP movie recording is started.
            if(SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_ON && uiNotifyAPPStatus)
            {
                WifiApp_SendCmd(WIFIAPP_CMD_NOTIFY_STATUS, WIFIAPP_RET_RECORD_STOPPED);
            }
            //#NT#2017/05/24#Isiah Chang -end

		} else if ((curStatus == WIFI_MOV_ST_RECORD) && (recordTime < 1)) {
			result = WIFIAPP_RET_FAIL;
			DBG_ERR("recTime<1 sec %d sts %d\r\n", recordTime, WiFiCmd_GetStatus());
		} else if (curStatus == WIFI_MOV_ST_IDLE) {
			result = WIFIAPP_RET_FAIL;
			DBG_ERR("idle state,cannot stop\r\n");
		}
	}
	// Notify Done
	//RTSP start OK should wait video read,so not return done
	//HTTP return done directly
//#NT#2016/05/31#Ben Wang -begin
//#NT#Add UVC multimedia function.
#if(UVC_MULTIMEDIA_FUNC == ENABLE)
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_UVC) {
		if (!((ImageApp_UsbMovie_GetConfig(NVT_USBMOVIE_CFG_MEDIA_FMT) == NVT_USBMOVIE_MEDIA_H264)
			  && (result == WIFIAPP_RET_OK))) {
			WifiCmd_Done(WIFIFLAG_RECORD_DONE, result);
		}
	} else
#endif
	{
#if _TODO
		if (!((ImageApp_NetMovie_GetConfig(NETMOVIE_CFG_MODE) == NETMOVIE_TYPE_RTSP)
			  && (result == WIFIAPP_RET_OK)))
#endif
		{

			WifiCmd_Done(WIFIFLAG_RECORD_DONE, result);
		}

	}
//#NT#2016/05/31#Ben Wang -end
	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeSetMovieRecSize(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
#if (WIFI_FINALCAM_APP_STYLE == ENABLE)
		// Transfer movie size index for FinalCam APP.
		switch (Data) {
		default:
		case FINALCAM_MOVIE_REC_SIZE_1080P:   // 1920 x 1080
			Data = MOVIE_SIZE_FRONT_1920x1080P30;
			break;

		case FINALCAM_MOVIE_REC_SIZE_720P:    // 1280 x 720
			Data = MOVIE_SIZE_FRONT_1280x720P30;
			break;

		case FINALCAM_MOVIE_REC_SIZE_WVGA:    // 854 x 480
			Data = MOVIE_SIZE_FRONT_848x480P30;
			break;

		case FINALCAM_MOVIE_REC_SIZE_VGA:     // 640 x 480
			Data = MOVIE_SIZE_FRONT_640x480P30;
			break;
		}
#endif

		//until start preview to set size and change mode
		UI_SetData(FL_MOVIE_SIZE_MENU, Data);
		//Ux_SendEvent(&CustomMovieObjCtrl,NVTEVT_EXE_MOVIESIZE, 1, Data);
		//Ux_SendEvent(&CustomMovieObjCtrl,NVTEVT_EXE_IMAGE_RATIO, 1, GetMovieSizeRatio(UI_GetData(FL_MOVIE_SIZE)));

		//check some menu item change ,we need to re open
#if (WIFI_FINALCAM_APP_STYLE == ENABLE)
		{
			BOOL bReOpen = FALSE;

			FlowWiFiMovie_Stop2Idle();  // Stop IPL setting first.

			Delay_DelayMs(100);  // Could be fine tuned.

			bReOpen = FlowMovie_CheckReOpenItem();

			if (bReOpen == TRUE) {
				Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 1, System_GetState(SYS_STATE_CURRMODE));
			} else {
				FlowWiFiMovie_StopRec();
			}
		}
#endif
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeCyclicRec(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_CYCLIC_REC, 1, Data);
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeMovieHDR(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

    if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD)
    {
        //until start preview to set size and change WDR,
        UI_SetData(FL_MOVIE_WDR_MENU,Data);
        //Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_HDR, 1, Data);
    }

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeSetMovieEV(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;
//#NT#2015/09/09#Janice Huang -begin
//#NT# photo and movie use the same EV value
#if 0
	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}
#endif
//#NT#2015/09/09#Janice Huang -end

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_EV, 1, Data);
	}

	return NVTEVT_CONSUME;
}
//#NT#2016/06/03#Charlie Chang -begin
//#NT# support contrast, two-way audio, flip_mirror, quality set
INT32 WiFiCmd_OnExeSetMovieContrast(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_CONTRAST, 1, Data);
	}

	return NVTEVT_CONSUME;
}
INT32 WiFiCmd_OnExeSetMovieAudioIn(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIOIN, 1, Data);
	}

	return NVTEVT_CONSUME;
}
INT32 WiFiCmd_OnExeSetMovieAudioInSR(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIOIN_SR, 1, Data);
	}

	return NVTEVT_CONSUME;
}
INT32 WiFiCmd_OnExeSetMovieFlipMirror(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_FLIP_MIRROR, 1, Data);
	}

	return NVTEVT_CONSUME;
}
INT32 WiFiCmd_OnExeSetMovieQualitySet(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;
	Data = paramNum ? paramArray[0] : 0;

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_QUALITY_SET, 1, Data);
	}

	return NVTEVT_CONSUME;
}
//#NT#2016/06/03#Charlie Chang -end
INT32 WiFiCmd_OnExeSetMotionDet(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOTION_DET, 1, Data);
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeSetMovieAudio(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIO, 1, Data);
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeSetMovieDateImprint(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_DATE_IMPRINT, 1, Data);
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeSetMovieLiveviewSize(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		UI_SetData(FL_WIFI_MOVIE_APP_PREVIEW_SIZE, Data);
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeSetMovieGSesnorSensitivity(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_GSENSOR, 1, Data);
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeSetAutoRecording(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 Data;

	Data = paramNum ? paramArray[0] : 0;

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
		UI_SetData(FL_WIFI_AUTO_RECORDING, Data);
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeSetMovieRecBitRate(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	char *Data = 0;
	UINT32 uiTargetBitRate;


	if (paramNum) {
		Data = (char *)paramArray[0];

		if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
			DBG_ERR("not movie mode\r\n");
			WifiCmd_UnlockString(Data);
			return NVTEVT_CONSUME;
		}

		if (1 == sscanf_s(Data, "%d", &uiTargetBitRate)) {
			if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
				debug_msg("Rec target bit rate:%d KBytes\r\n", uiTargetBitRate);
				SetMovieTargetBitrate(1, UI_GetData(FL_MOVIE_SIZE), uiTargetBitRate * 1024);
			}
		}
		WifiCmd_UnlockString(Data);
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnExeSetMovieLiveviewBitRate(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	char *Data = 0;
	UINT32 uiTargetBitRate;

	if (paramNum) {
		Data = (char *)paramArray[0];

		if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
			DBG_ERR("not movie mode\r\n");
			WifiCmd_UnlockString(Data);
			return NVTEVT_CONSUME;
		}

		if (1 == sscanf_s(Data, "%d", &uiTargetBitRate)) {
			if (WiFiCmd_GetStatus() != WIFI_MOV_ST_RECORD) {
				debug_msg("Preview target bit rate:%d KBytes\r\n", uiTargetBitRate);
				SetMovieTargetBitrate(0, UI_GetData(FL_WIFI_MOVIE_APP_PREVIEW_SIZE), uiTargetBitRate * 1024);
			}
		}
		WifiCmd_UnlockString(Data);
	}

	return NVTEVT_CONSUME;
}

//#NT#2017/01/03#Isiah Chang -begin
//#NT#Add WiFiCmd Bitrate control.
BOOL WiFiCmd_BRC_AutoRunStateGet(void)
{
	return g_BRCAutoRun;
}

void WiFiCmd_BRC_reset(void)
{
	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		debug_err(("not movie mode\r\n"));
	}

	g_BRCUpperBound = GetMovieTargetBitrate_2p(1, UI_GetData(FL_MOVIE_SIZE));
#if 0
	g_BRCLowerBound = g_BRCUpperBound * 20 / 100; // 80% adjust range
#else
	g_BRCLowerBound = 1 * 1024; // 1KB. //g_BRCUpperBound*5/100; // 95% adjust range
#endif

	g_BRCTotalLevel = 10; // Total 10 levels range to be adjusted.
	g_BRCCurrentLevel = g_BRCTotalLevel; //Init value

#if _TODO
	MovRec_EnUnlimitedLowTBR(1);  // No limit lowest target bit rate.
#endif
}

//#NT#2018/04/02#IsiahChang -begin
//#NT#To support Wi-Fi command 2025 BRC.
INT32 WiFiCmd_BRCAdjust(INT32 iLevel)
{

	UINT32 TargetBitrate;
    MP_VDOENC_CBR_INFO tStreamCbrInfo = {0};

	if (g_BRCUpperBound != GetMovieTargetBitrate_2p(1, UI_GetData(FL_MOVIE_SIZE))) {
		WiFiCmd_BRC_reset();
		return NVTEVT_CONSUME;
	}

	DBG_IND("iLevel %d\r\n", iLevel);

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		debug_err(("not movie mode\r\n"));
		return NVTEVT_CONSUME;
	}

	if (iLevel) {
		if (iLevel == 8000) {
			g_BRCAutoRun = FALSE;
		} else if (iLevel == 8001) {
			g_BRCAutoRun = TRUE;  // Enable BRC AutoRun. BRC level will be decreased if HB was lost for a while.
		} else {
			g_BRCCurrentLevel += iLevel;
		}
	} else {
		//g_BRCCurrentLevel = g_BRCTotalLevel;
	}

	if (g_BRCCurrentLevel < 0) {
		g_BRCCurrentLevel = 0;
	} else if (g_BRCCurrentLevel > g_BRCTotalLevel) {
		g_BRCCurrentLevel = g_BRCTotalLevel;
	}

	if (g_BRCCurrentLevel > 6) {
		g_BRCLowerBound = g_BRCUpperBound / 5;
		TargetBitrate = g_BRCLowerBound + (g_BRCUpperBound - g_BRCLowerBound) * (g_BRCCurrentLevel - 6) / 4;
	} else {
		g_BRCLowerBound = 1 * 1024; // 1KB.
		TargetBitrate = g_BRCLowerBound + (g_BRCUpperBound / 5 - g_BRCLowerBound) * g_BRCCurrentLevel / 6;

	}

	DBG_IND("Total Lvl:%d, CurLvl:%d, UpBound:%d, LowBound:%d, TargetBitRate:%d\r\n", \
			g_BRCTotalLevel, g_BRCCurrentLevel, g_BRCUpperBound, g_BRCLowerBound, TargetBitrate);

	// Modify uiByteRate member var in MOVIE_CFG_CBR_INFO sturcture for bit rate manipulation.
#if MOVIE_MAPPING_MULTIREC
	NMR_VdoEnc_GetCBR(ImageApp_MovieMulti_GetVdoEncPort(_CFG_STRM_ID_1), &tStreamCbrInfo);
	ImageApp_MovieMulti_SetParam(_CFG_STRM_ID_1, MOVIEMULTI_PARAM_CBR_INFO, (UINT32)&(tStreamCbrInfo));
#else
	NMR_VdoEnc_GetCBR(ImageApp_Movie_GetVdoEncPort(_CFG_STRM_ID_1), &tStreamCbrInfo);
	ImageApp_Movie_SetParam(_CFG_STRM_ID_1, MOVIE_PARAM_CBR_INFO, (UINT32)&(tStreamCbrInfo));
#endif
    tStreamCbrInfo.uiByteRate = TargetBitrate;

	return NVTEVT_CONSUME;
}
//#NT#2018/04/02#IsiahChang -end
//#NT#2017/01/03#Isiah Chang -end

INT32 WiFiCmd_OnExeMovieLiveviewStart(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	BOOL startLview = 0;
	UINT32 result = WIFIAPP_RET_OK;
	UINT32 curStatus = 0;
//#NT#2016/08/29#Isiah Chang -begin
//#NT# [mantis 0107729: return error if no paramter was given.
	if (paramNum > 0) {
		startLview = paramArray[0];
	} else {
		WifiCmd_Done(WIFIFLAG_PREVIEW_DONE, WIFIAPP_RET_PAR_ERR);
		DBG_ERR("too few par!\r\n");
		return NVTEVT_CONSUME;
	}
//#NT#2016/08/29#Isiah Chang -end

	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		WifiCmd_Done(WIFIFLAG_PREVIEW_DONE, WIFIAPP_RET_STATE_ERR);
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	curStatus = WiFiCmd_GetStatus();

	if (startLview) {
		//#NT#2016/05/31#Ben Wang -begin
		//#NT#Add UVC multimedia function.
#if(UVC_MULTIMEDIA_FUNC == ENABLE)
		if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_UVC) {
			BOOL bIsWifiH264Stream = FALSE;
			if (ImageApp_UsbMovie_GetConfig(NVT_USBMOVIE_CFG_MEDIA_FMT) == NVT_USBMOVIE_MEDIA_H264) {
				bIsWifiH264Stream = TRUE;
			}
			if (((curStatus == WIFI_MOV_ST_IDLE) && (bIsWifiH264Stream == TRUE))
				|| ((curStatus == WIFI_MOV_ST_LVIEW) && (bIsWifiH264Stream == FALSE))) {
				FlowWiFiMovie_StopRec();
			} else if (curStatus == WIFI_MOV_ST_RECORD) {
				result = WIFIAPP_RET_FAIL;
				DBG_ERR("recording\r\n");
			}
		} else
#endif
		{
			if (curStatus == WIFI_MOV_ST_IDLE) {
                //check some menu item change ,we need to re open
                BOOL bReOpen = FlowMovie_CheckReOpenItem();

                if(bReOpen==TRUE)
                {
                    Ux_SendEvent(0,NVTEVT_SYSTEM_MODE, 1, System_GetState(SYS_STATE_CURRMODE));
                }
                else
                {
                    FlowWiFiMovie_StartLview();
                }
            } else if (curStatus == WIFI_MOV_ST_RECORD) {
				result = WIFIAPP_RET_FAIL;
				DBG_ERR("recording\r\n");
			}
		}
		//#NT#2016/05/31#Ben Wang -end
	} else {
		if (curStatus == WIFI_MOV_ST_LVIEW) {
			FlowWiFiMovie_Stop2Idle();
		} else if (curStatus == WIFI_MOV_ST_RECORD) {
			result = WIFIAPP_RET_FAIL;
			DBG_ERR("recording\r\n");
		}
	}

	WifiCmd_Done(WIFIFLAG_PREVIEW_DONE, result); // signal wi-fi app cmd is done.
	return NVTEVT_CONSUME;
}




INT32 WiFiCmd_OnExeTriggerMovieRawEnc(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 result = WIFIAPP_RET_OK;
	//UINT32 curStatus = 0;
	UINT32 uiJpegWidth, uiJpegHeight, uiDAR, uiMovieSize;


	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		WifiCmd_Done(WIFIFLAG_PREVIEW_DONE, WIFIAPP_RET_STATE_ERR);
		DBG_ERR("not movie mode\r\n");
		return NVTEVT_CONSUME;
	}

	//680,510 media not record,also can raw encode
#if (MOVIE_MAPPING_MULTIREC == ENABLE)
	if (ImageApp_MovieMulti_IsStreamRunning(_CFG_REC_ID_1) ||
		ImageApp_MovieMulti_IsStreamRunning(_CFG_REC_ID_2) ||
		ImageApp_MovieMulti_IsStreamRunning(_CFG_REC_ID_3) ||
		ImageApp_MovieMulti_IsStreamRunning(_CFG_REC_ID_4)) {
#else
	if (ImageApp_Movie_Is_Stream_Running(_CFG_REC_ID_1)) {
#endif
		uiMovieSize = UI_GetData(FL_MOVIE_SIZE);
		uiJpegWidth = GetMovieSizeWidth(uiMovieSize);
		uiJpegHeight = GetMovieSizeHeight(uiMovieSize);
		uiDAR = GetMovieDispAspectRatio(uiMovieSize);
		if (uiDAR == MP_VDOENC_DAR_16_9) {
			uiJpegWidth = (uiJpegHeight * 16) / 9;
		}

		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_REC_RAWENC, 2, uiJpegWidth, uiJpegHeight);
	} else {
		result = WIFIAPP_RET_FAIL;
		DBG_ERR("Not in recording state\r\n");

		WifiCmd_Done(WIFIFLAG_MOVIE_REC_RAWENC_DONE, result); // signal wi-fi app cmd is done.
	}

	return NVTEVT_CONSUME;
}
INT32 WiFiCmd_OnExeMovieBRCAdjust(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	if (paramNum) {
		WiFiCmd_BRCAdjust((INT32)paramArray[0]);
		return 0;
	} else {
		return -1;
	}
}
INT32 WiFiCmd_OnMovieFull(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	DBG_ERR("%s \r\n", __FUNCTION__);
	WifiApp_SendCmd(WIFIAPP_CMD_NOTIFY_STATUS, WIFIAPP_RET_MOVIE_FULL);

	//moive is stopped by media record library;project need to stop RTSP
#if(WIFI_AP_FUNC==ENABLE)
	//Ux_SendEvent(&UIMovieRecObjCtrl, NVTEVT_STOP_RTSP, 0);
	//ImageApp_CamMovie_RegRTSPSetBSCB(NULL);
	//ImageUnit_SetParam(&ISF_Media, MEDIA_PARAM_BITSTREAM_CB, 0);  //obsoleted
	//RtspNvt_Close();
#endif
	FlowMovie_SetRecCurrTime(0);
	FlowWiFiMovie_StopRec();

	return NVTEVT_CONSUME;
}
INT32 WiFiCmd_OnMovieWrError(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	DBG_ERR("%s \r\n", __FUNCTION__);

	// Something wrong with card. Mark file system error status.
	System_SetState(SYS_STATE_FS, FS_DISK_ERROR);
	WifiApp_SendCmd(WIFIAPP_CMD_NOTIFY_STATUS, WIFIAPP_RET_MOVIE_WR_ERROR);

	//moive is stopped by media record library;project need to stop RTSP
#if(WIFI_AP_FUNC==ENABLE)
	//Ux_SendEvent(&UIMovieRecObjCtrl, NVTEVT_STOP_RTSP, 0);
	//ImageApp_CamMovie_RegRTSPSetBSCB(NULL);
	//ImageUnit_SetParam(&ISF_Media, MEDIA_PARAM_BITSTREAM_CB, 0);  //obsoleted
	//RtspNvt_Close();
#endif
	FlowMovie_SetRecCurrTime(0);
	FlowWiFiMovie_StopRec();

	return NVTEVT_CONSUME;
}
INT32 WiFiCmd_OnStorageSlow(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	DBG_ERR("%s \r\n", __FUNCTION__);
	WifiApp_SendCmd(WIFIAPP_CMD_NOTIFY_STATUS, WIFIAPP_RET_MOVIE_SLOW);

	//moive is stopped by media record library;project need to stop RTSP
#if 0
	Ux_SendEvent(&UIMovieRecObjCtrl, NVTEVT_STOP_RTSP, 0);
	FlowMovie_SetRecCurrTime(0);
	FlowWiFiMovie_StartRec(WIFI_RTSP_LIVEVIEW);
#else // Restart recording automatically when slow card event occurred.
	FlowMovie_SetRecCurrTime(0);
	FlowWiFiMovie_StartRec();
#endif

	return NVTEVT_CONSUME;
}
INT32 WiFiCmd_OnMovieOneSec(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD && paramNum) {
		//DBGD(paramArray[0]);
		FlowMovie_SetRecCurrTime(paramArray[0]);
		//WifiApp_SendCmd(WIFIAPP_CMD_NOTIFY_MOVIETIME,paramArray[0]);
	}

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnMovieRawEncJpgOKCB(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 result = WIFIAPP_RET_OK;

	WifiCmd_Done(WIFIFLAG_MOVIE_REC_RAWENC_DONE, result); // signal wi-fi app cmd is done.

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_OnMovieRawEncErr(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 result = WIFIAPP_RET_FAIL;

	WifiCmd_Done(WIFIFLAG_MOVIE_REC_RAWENC_DONE, result); // signal wi-fi app cmd is done.

	return NVTEVT_CONSUME;
}

INT32 WiFiCmd_GetStatus(void)
{
	UINT32 status;
//#NT#2016/05/31#Ben Wang -begin
//#NT#Add UVC multimedia function.
//	BOOL bIsWifiH264Stream = FALSE;
#if(UVC_MULTIMEDIA_FUNC == ENABLE)
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_UVC) {
		if (ImageApp_UsbMovie_GetConfig(NVT_USBMOVIE_CFG_MEDIA_FMT) == NVT_USBMOVIE_MEDIA_H264) {
			bIsWifiH264Stream = TRUE;
		}
	} else
#endif
	{
#if (MOVIE_MAPPING_MULTIREC == ENABLE)
	if (ImageApp_MovieMulti_IsStreamRunning(_CFG_REC_ID_1) ||
		ImageApp_MovieMulti_IsStreamRunning(_CFG_REC_ID_2) ||
		ImageApp_MovieMulti_IsStreamRunning(_CFG_REC_ID_3) ||
		ImageApp_MovieMulti_IsStreamRunning(_CFG_REC_ID_4)) {
#else
		if (ImageApp_Movie_Is_Stream_Running(_CFG_REC_ID_1) == TRUE) {
#endif
			status = WIFI_MOV_ST_RECORD;
#if (MOVIE_MAPPING_MULTIREC == ENABLE)
		} else if (ImageApp_MovieMulti_IsStreamRunning(_CFG_STRM_ID_1) == TRUE) {
#else
		} else if (ImageApp_Movie_Is_Stream_Running(_CFG_STRM_ID_1) == TRUE) {
#endif
			status = WIFI_MOV_ST_LVIEW;
		} else
			status = WIFI_MOV_ST_IDLE;
	}

	return status;
}
#endif

