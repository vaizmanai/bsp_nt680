/**
    IPL dzoom table sample.

    @file       ipl_dzoom_tab_ov12895m_evb.c
    @ingroup    mISYSAlg
    @note       Nothing (or anything need to be mentioned).

    Copyright   Novatek Microelectronics Corp. 2011.  All rights reserved.
*/

#include "ipl_ov12895m_evb_int.h"

static IPL_DZOOM_SEL_INFO sensor_mode_dzoom_table[] = {
//special case for sensor auto gen
	//{SENSOR_MODE_1,61,8,0,0,IPL_CROP},
};
const UINT32 VDOZOOM_INFOR_MODE_1_TABLE[61][DZOOM_ITEM_MAX] = {
    {4096, 3072, 4096, 3072, 4096, 3072, 4096, 3072}, //1
    {4096, 2160, 4096, 2160, 3956, 2088, 3956, 2088}, //2
    {4096, 2160, 4096, 2160, 3820, 2016, 3820, 2016}, //3
    {4096, 2160, 4096, 2160, 3692, 1948, 3692, 1948}, //4
    {4096, 2160, 4096, 2160, 3564, 1880, 3564, 1880}, //5
    {4096, 2160, 4096, 2160, 3444, 1816, 3444, 1816}, //6
    {4096, 2160, 4096, 2160, 3328, 1756, 3328, 1756}, //7
    {4096, 2160, 4096, 2160, 3212, 1696, 3212, 1696}, //8
    {4096, 2160, 4096, 2160, 3104, 1636, 3104, 1636}, //9
    {4060, 2140, 4060, 2140, 3000, 1580, 3000, 1580}, //10
    {4008, 2112, 4008, 2112, 2896, 1528, 2896, 1528}, //11
    {3956, 2088, 3956, 2088, 2796, 1476, 2796, 1476}, //12
    {3912, 2060, 3912, 2060, 2704, 1424, 2704, 1424}, //13
    {3864, 2036, 3864, 2036, 2612, 1376, 2612, 1376}, //14
    {3820, 2012, 3820, 2012, 2520, 1328, 2520, 1328}, //15
    {3776, 1992, 3776, 1992, 2436, 1284, 2436, 1284}, //16
    {3736, 1968, 3736, 1968, 2352, 1240, 2352, 1240}, //17
    {3696, 1948, 3696, 1948, 2272, 1200, 2272, 1200}, //18
    {3656, 1928, 3656, 1928, 2196, 1156, 2196, 1156}, //19
    {3620, 1908, 3620, 1908, 2120, 1120, 2120, 1120}, //20
    {2560, 1348, 2560, 1348, 2048, 1080, 2048, 1080}, //21
    {2492, 1312, 2492, 1312, 1980, 1044, 1980, 1044}, //22
    {2424, 1276, 2424, 1276, 1912, 1008, 1912, 1008}, //23
    {2356, 1240, 2356, 1240, 1844,  972, 1844,  972}, //24
    {2296, 1208, 2296, 1208, 1784,  940, 1784,  940}, //25
    {2236, 1180, 2236, 1180, 1724,  908, 1724,  908}, //26
    {2176, 1148, 2176, 1148, 1664,  876, 1664,  876}, //27
    {2120, 1116, 2120, 1116, 1608,  848, 1608,  848}, //28
    {2064, 1088, 2064, 1088, 1552,  820, 1552,  820}, //29
    {2012, 1060, 2012, 1060, 1500,  792, 1500,  792}, //30
    {1960, 1032, 1960, 1032, 1448,  764, 1448,  764}, //31
    {1912, 1008, 1912, 1008, 1400,  736, 1400,  736}, //32
    {1864,  980, 1864,  980, 1352,  712, 1352,  712}, //33
    {1816,  956, 1816,  956, 1304,  688, 1304,  688}, //34
    {1772,  932, 1772,  932, 1260,  664, 1260,  664}, //35
    {1728,  912, 1728,  912, 1216,  644, 1216,  644}, //36
    {1688,  888, 1688,  888, 1176,  620, 1176,  620}, //37
    {1648,  868, 1648,  868, 1136,  600, 1136,  600}, //38
    {1608,  848, 1608,  848, 1096,  580, 1096,  580}, //39
    {1572,  828, 1572,  828, 1060,  560, 1060,  560}, //40
    {1536,  808, 1536,  808, 1024,  540, 1024,  540}, //41
    {1500,  788, 1500,  788,  988,  520,  988,  520}, //42
    {1468,  772, 1468,  772,  956,  504,  956,  504}, //43
    {1436,  756, 1436,  756,  924,  488,  924,  488}, //44
    {1404,  740, 1404,  740,  892,  472,  892,  472}, //45
    {1372,  724, 1372,  724,  860,  456,  860,  456}, //46
    {1344,  708, 1344,  708,  832,  440,  832,  440}, //47
    {1316,  692, 1316,  692,  804,  424,  804,  424}, //48
    {1288,  680, 1288,  680,  776,  408,  776,  408}, //49
    {1260,  664, 1260,  664,  748,  396,  748,  396}, //50
    {1236,  652, 1236,  652,  724,  380,  724,  380}, //51
    {1212,  640, 1212,  640,  700,  368,  700,  368}, //52
    {1188,  624, 1188,  624,  676,  356,  676,  356}, //53
    {1164,  612, 1164,  612,  652,  344,  652,  344}, //54
    {1144,  604, 1144,  604,  632,  332,  632,  332}, //55
    {1120,  588, 1120,  588,  608,  320,  608,  320}, //56
    {1100,  580, 1100,  580,  588,  312,  588,  312}, //57
    {1080,  568, 1080,  568,  568,  300,  568,  300}, //58
    {1060,  556, 1060,  556,  548,  288,  548,  288}, //59
    {1044,  548, 1044,  548,  532,  280,  532,  280}, //60
    {1024,  540, 1024,  540,  512,  268,  512,  268}, //61
};

const UINT32 VDOZOOM_INFOR_MODE_2_TABLE[61][DZOOM_ITEM_MAX] = {
    {3840, 2160, 3840, 2160, 3840, 2160, 3840, 2160}, //1

    {2048, 1080, 2048, 1080, 1980, 1044, 1980, 1044}, //2
    {2048, 1080, 2048, 1080, 1912, 1008, 1912, 1008}, //3
    {2048, 1080, 2048, 1080, 1844,  972, 1844,  972}, //4
    {2048, 1080, 2048, 1080, 1784,  940, 1784,  940}, //5
    {2048, 1080, 2048, 1080, 1724,  908, 1724,  908}, //6
    {2048, 1080, 2048, 1080, 1664,  876, 1664,  876}, //7
    {2048, 1080, 2048, 1080, 1608,  848, 1608,  848}, //8
    {2048, 1080, 2048, 1080, 1552,  820, 1552,  820}, //9
    {2048, 1080, 2048, 1080, 1500,  792, 1500,  792}, //10
    {2048, 1080, 2048, 1080, 1448,  764, 1448,  764}, //11
    {2048, 1080, 2048, 1080, 1400,  736, 1400,  736}, //12
    {2048, 1080, 2048, 1080, 1352,  712, 1352,  712}, //13
    {2048, 1080, 2048, 1080, 1304,  688, 1304,  688}, //14
    {2048, 1080, 2048, 1080, 1260,  664, 1260,  664}, //15
    {2048, 1080, 2048, 1080, 1216,  644, 1216,  644}, //16
    {2048, 1080, 2048, 1080, 1176,  620, 1176,  620}, //17
    {2048, 1080, 2048, 1080, 1136,  600, 1136,  600}, //18
    {2048, 1080, 2048, 1080, 1096,  580, 1096,  580}, //19
    {2048, 1080, 2048, 1080, 1060,  560, 1060,  560}, //20
    {1536,  808, 1536,  808, 1024,  540, 1024,  540}, //21
    {1500,  788, 1500,  788,  988,  520,  988,  520}, //22
    {1468,  772, 1468,  772,  956,  504,  956,  504}, //23
    {1436,  756, 1436,  756,  924,  488,  924,  488}, //24
    {1404,  740, 1404,  740,  892,  472,  892,  472}, //25
    {1372,  724, 1372,  724,  860,  456,  860,  456}, //26
    {1344,  708, 1344,  708,  832,  440,  832,  440}, //27
    {1316,  692, 1316,  692,  804,  424,  804,  424}, //28
    {1288,  680, 1288,  680,  776,  408,  776,  408}, //29
    {1260,  664, 1260,  664,  748,  396,  748,  396}, //30
    {1236,  652, 1236,  652,  724,  380,  724,  380}, //31
    {1212,  640, 1212,  640,  700,  368,  700,  368}, //32
    {1188,  624, 1188,  624,  676,  356,  676,  356}, //33
    {1164,  612, 1164,  612,  652,  344,  652,  344}, //34
    {1144,  604, 1144,  604,  632,  332,  632,  332}, //35
    {1120,  588, 1120,  588,  608,  320,  608,  320}, //36
    {1100,  580, 1100,  580,  588,  312,  588,  312}, //37
    {1080,  568, 1080,  568,  568,  300,  568,  300}, //38
    {1060,  556, 1060,  556,  548,  288,  548,  288}, //39
    {1044,  548, 1044,  548,  532,  280,  532,  280}, //40
    {1024,  540, 1024,  540,  512,  268,  512,  268}, //41
    {1008,  532, 1008,  532,  496,  260,  496,  260}, //42
    { 988,  520,  988,  520,  476,  252,  476,  252}, //43
    { 972,  512,  972,  512,  460,  244,  460,  244}, //44
    { 956,  504,  956,  504,  444,  236,  444,  236}, //45
    { 944,  496,  944,  496,  432,  228,  432,  228}, //46
    { 928,  488,  928,  488,  416,  220,  416,  220}, //47
    { 912,  480,  912,  480,  400,  212,  400,  212}, //48
    { 900,  472,  900,  472,  388,  204,  388,  204}, //49
    { 888,  468,  888,  468,  376,  196,  376,  196}, //50
    { 876,  460,  876,  460,  364,  192,  364,  192}, //51
    { 860,  452,  860,  452,  348,  184,  348,  184}, //52
    { 848,  448,  848,  448,  336,  180,  336,  180}, //53
    { 840,  440,  840,  440,  328,  172,  328,  172}, //54
    { 828,  436,  828,  436,  316,  168,  316,  168}, //55
    { 816,  428,  816,  428,  304,  160,  304,  160}, //56
    { 808,  424,  808,  424,  296,  156,  296,  156}, //57
    { 796,  420,  796,  420,  284,  148,  284,  148}, //58
    { 788,  416,  788,  416,  276,  144,  276,  144}, //59
    { 776,  408,  776,  408,  264,  140,  264,  140}, //60
    { 768,  404,  768,  404,  256,  136,  256,  136}, //61
};

const UINT32 VDOZOOM_INFOR_MODE_2_TABLE_1920x1080[61][DZOOM_ITEM_MAX] = {
    {3840, 2160, 2560, 1440, 2560, 1440, 3840, 2160}, //1

    {2048, 1080, 2048, 1080, 1980, 1044, 1980, 1044}, //2
    {2048, 1080, 2048, 1080, 1912, 1008, 1912, 1008}, //3
    {2048, 1080, 2048, 1080, 1844,  972, 1844,  972}, //4
    {2048, 1080, 2048, 1080, 1784,  940, 1784,  940}, //5
    {2048, 1080, 2048, 1080, 1724,  908, 1724,  908}, //6
    {2048, 1080, 2048, 1080, 1664,  876, 1664,  876}, //7
    {2048, 1080, 2048, 1080, 1608,  848, 1608,  848}, //8
    {2048, 1080, 2048, 1080, 1552,  820, 1552,  820}, //9
    {2048, 1080, 2048, 1080, 1500,  792, 1500,  792}, //10
    {2048, 1080, 2048, 1080, 1448,  764, 1448,  764}, //11
    {2048, 1080, 2048, 1080, 1400,  736, 1400,  736}, //12
    {2048, 1080, 2048, 1080, 1352,  712, 1352,  712}, //13
    {2048, 1080, 2048, 1080, 1304,  688, 1304,  688}, //14
    {2048, 1080, 2048, 1080, 1260,  664, 1260,  664}, //15
    {2048, 1080, 2048, 1080, 1216,  644, 1216,  644}, //16
    {2048, 1080, 2048, 1080, 1176,  620, 1176,  620}, //17
    {2048, 1080, 2048, 1080, 1136,  600, 1136,  600}, //18
    {2048, 1080, 2048, 1080, 1096,  580, 1096,  580}, //19
    {2048, 1080, 2048, 1080, 1060,  560, 1060,  560}, //20
    {1536,  808, 1536,  808, 1024,  540, 1024,  540}, //21
    {1500,  788, 1500,  788,  988,  520,  988,  520}, //22
    {1468,  772, 1468,  772,  956,  504,  956,  504}, //23
    {1436,  756, 1436,  756,  924,  488,  924,  488}, //24
    {1404,  740, 1404,  740,  892,  472,  892,  472}, //25
    {1372,  724, 1372,  724,  860,  456,  860,  456}, //26
    {1344,  708, 1344,  708,  832,  440,  832,  440}, //27
    {1316,  692, 1316,  692,  804,  424,  804,  424}, //28
    {1288,  680, 1288,  680,  776,  408,  776,  408}, //29
    {1260,  664, 1260,  664,  748,  396,  748,  396}, //30
    {1236,  652, 1236,  652,  724,  380,  724,  380}, //31
    {1212,  640, 1212,  640,  700,  368,  700,  368}, //32
    {1188,  624, 1188,  624,  676,  356,  676,  356}, //33
    {1164,  612, 1164,  612,  652,  344,  652,  344}, //34
    {1144,  604, 1144,  604,  632,  332,  632,  332}, //35
    {1120,  588, 1120,  588,  608,  320,  608,  320}, //36
    {1100,  580, 1100,  580,  588,  312,  588,  312}, //37
    {1080,  568, 1080,  568,  568,  300,  568,  300}, //38
    {1060,  556, 1060,  556,  548,  288,  548,  288}, //39
    {1044,  548, 1044,  548,  532,  280,  532,  280}, //40
    {1024,  540, 1024,  540,  512,  268,  512,  268}, //41
    {1008,  532, 1008,  532,  496,  260,  496,  260}, //42
    { 988,  520,  988,  520,  476,  252,  476,  252}, //43
    { 972,  512,  972,  512,  460,  244,  460,  244}, //44
    { 956,  504,  956,  504,  444,  236,  444,  236}, //45
    { 944,  496,  944,  496,  432,  228,  432,  228}, //46
    { 928,  488,  928,  488,  416,  220,  416,  220}, //47
    { 912,  480,  912,  480,  400,  212,  400,  212}, //48
    { 900,  472,  900,  472,  388,  204,  388,  204}, //49
    { 888,  468,  888,  468,  376,  196,  376,  196}, //50
    { 876,  460,  876,  460,  364,  192,  364,  192}, //51
    { 860,  452,  860,  452,  348,  184,  348,  184}, //52
    { 848,  448,  848,  448,  336,  180,  336,  180}, //53
    { 840,  440,  840,  440,  328,  172,  328,  172}, //54
    { 828,  436,  828,  436,  316,  168,  316,  168}, //55
    { 816,  428,  816,  428,  304,  160,  304,  160}, //56
    { 808,  424,  808,  424,  296,  156,  296,  156}, //57
    { 796,  420,  796,  420,  284,  148,  284,  148}, //58
    { 788,  416,  788,  416,  276,  144,  276,  144}, //59
    { 776,  408,  776,  408,  264,  140,  264,  140}, //60
    { 768,  404,  768,  404,  256,  136,  256,  136}, //61
};

const UINT32 VDOZOOM_INFOR_MODE_3_TABLE[61][DZOOM_ITEM_MAX] = {
    {2048, 1536, 2048, 1536, 2048, 1536, 2048, 1536}, //1
    {1364,  720, 1364,  720, 1316,  696, 1316,  696}, //2
    {1364,  720, 1364,  720, 1272,  672, 1272,  672}, //3
    {1364,  720, 1364,  720, 1228,  648, 1228,  648}, //4
    {1364,  720, 1364,  720, 1188,  628, 1188,  628}, //5
    {1364,  720, 1364,  720, 1148,  604, 1148,  604}, //6
    {1364,  720, 1364,  720, 1108,  584, 1108,  584}, //7
    {1364,  720, 1364,  720, 1072,  564, 1072,  564}, //8
    {1364,  720, 1364,  720, 1032,  544, 1032,  544}, //9
    {1364,  720, 1364,  720, 1000,  528, 1000,  528}, //10
    {1364,  720, 1364,  720,  964,  508,  964,  508}, //11
    {1364,  720, 1364,  720,  932,  492,  932,  492}, //12
    {1364,  720, 1364,  720,  900,  476,  900,  476}, //13
    {1364,  720, 1364,  720,  868,  460,  868,  460}, //14
    {1364,  720, 1364,  720,  840,  444,  840,  444}, //15
    {1364,  720, 1364,  720,  812,  428,  812,  428}, //16
    {1364,  720, 1364,  720,  784,  412,  784,  412}, //17
    {1364,  720, 1364,  720,  756,  400,  756,  400}, //18
    {1364,  720, 1364,  720,  732,  384,  732,  384}, //19
    {1364,  720, 1364,  720,  708,  372,  708,  372}, //20
    {1196,  632, 1196,  632,  684,  360,  684,  360}, //21
    {1172,  616, 1172,  616,  660,  348,  660,  348}, //22
    {1148,  604, 1148,  604,  636,  336,  636,  336}, //23
    {1128,  596, 1128,  596,  616,  324,  616,  324}, //24
    {1104,  580, 1104,  580,  592,  312,  592,  312}, //25
    {1084,  572, 1084,  572,  572,  304,  572,  304}, //26
    {1064,  560, 1064,  560,  552,  292,  552,  292}, //27
    {1048,  552, 1048,  552,  536,  284,  536,  284}, //28
    {1028,  540, 1028,  540,  516,  272,  516,  272}, //29
    {1012,  532, 1012,  532,  500,  264,  500,  264}, //30
    { 996,  524,  996,  524,  484,  256,  484,  256}, //31
    { 976,  516,  976,  516,  464,  244,  464,  244}, //32
    { 960,  504,  960,  504,  448,  236,  448,  236}, //33
    { 948,  500,  948,  500,  436,  228,  436,  228}, //34
    { 932,  492,  932,  492,  420,  220,  420,  220}, //35
    { 916,  484,  916,  484,  404,  216,  404,  216}, //36
    { 904,  476,  904,  476,  392,  208,  392,  208}, //37
    { 892,  468,  892,  468,  380,  200,  380,  200}, //38
    { 876,  460,  876,  460,  364,  192,  364,  192}, //39
    { 864,  456,  864,  456,  352,  188,  352,  188}, //40
    { 852,  448,  852,  448,  340,  180,  340,  180}, //41
    { 840,  444,  840,  444,  328,  172,  328,  172}, //42
    { 832,  440,  832,  440,  320,  168,  320,  168}, //43
    { 820,  432,  820,  432,  308,  164,  308,  164}, //44
    { 808,  424,  808,  424,  296,  156,  296,  156}, //45
    { 800,  420,  800,  420,  288,  152,  288,  152}, //46
    { 788,  416,  788,  416,  276,  148,  276,  148}, //47
    { 780,  412,  780,  412,  268,  140,  268,  140}, //48
    { 772,  408,  772,  408,  260,  136,  260,  136}, //49
    { 760,  400,  760,  400,  248,  132,  248,  132}, //50
    { 752,  396,  752,  396,  240,  128,  240,  128}, //51
    { 744,  392,  744,  392,  232,  124,  232,  124}, //52
    { 736,  388,  736,  388,  224,  120,  224,  120}, //53
    { 728,  384,  728,  384,  216,  116,  216,  116}, //54
    { 720,  380,  720,  380,  208,  112,  208,  112}, //55
    { 716,  376,  716,  376,  204,  108,  204,  108}, //56
    { 708,  372,  708,  372,  196,  104,  196,  104}, //57
    { 700,  368,  700,  368,  188,  100,  188,  100}, //58
    { 696,  368,  696,  368,  184,   96,  184,   96}, //59
    { 688,  364,  688,  364,  176,   92,  176,   92}, //60
    { 684,  360,  684,  360,  172,   88,  172,   88}, //61
};

const UINT32 VDOZOOM_INFOR_MODE_4_TABLE[61][DZOOM_ITEM_MAX] = {
    {1920, 1080, 1920, 1080, 1920, 1080, 1920, 1080}, //1
    {1364,  720, 1364,  720, 1316,  696, 1316,  696}, //2
    {1364,  720, 1364,  720, 1272,  672, 1272,  672}, //3
    {1364,  720, 1364,  720, 1228,  648, 1228,  648}, //4
    {1364,  720, 1364,  720, 1188,  628, 1188,  628}, //5
    {1364,  720, 1364,  720, 1148,  604, 1148,  604}, //6
    {1364,  720, 1364,  720, 1108,  584, 1108,  584}, //7
    {1364,  720, 1364,  720, 1072,  564, 1072,  564}, //8
    {1364,  720, 1364,  720, 1032,  544, 1032,  544}, //9
    {1364,  720, 1364,  720, 1000,  528, 1000,  528}, //10
    {1364,  720, 1364,  720,  964,  508,  964,  508}, //11
    {1364,  720, 1364,  720,  932,  492,  932,  492}, //12
    {1364,  720, 1364,  720,  900,  476,  900,  476}, //13
    {1364,  720, 1364,  720,  868,  460,  868,  460}, //14
    {1364,  720, 1364,  720,  840,  444,  840,  444}, //15
    {1364,  720, 1364,  720,  812,  428,  812,  428}, //16
    {1364,  720, 1364,  720,  784,  412,  784,  412}, //17
    {1364,  720, 1364,  720,  756,  400,  756,  400}, //18
    {1364,  720, 1364,  720,  732,  384,  732,  384}, //19
    {1364,  720, 1364,  720,  708,  372,  708,  372}, //20
    {1196,  632, 1196,  632,  684,  360,  684,  360}, //21
    {1172,  616, 1172,  616,  660,  348,  660,  348}, //22
    {1148,  604, 1148,  604,  636,  336,  636,  336}, //23
    {1128,  596, 1128,  596,  616,  324,  616,  324}, //24
    {1104,  580, 1104,  580,  592,  312,  592,  312}, //25
    {1084,  572, 1084,  572,  572,  304,  572,  304}, //26
    {1064,  560, 1064,  560,  552,  292,  552,  292}, //27
    {1048,  552, 1048,  552,  536,  284,  536,  284}, //28
    {1028,  540, 1028,  540,  516,  272,  516,  272}, //29
    {1012,  532, 1012,  532,  500,  264,  500,  264}, //30
    { 996,  524,  996,  524,  484,  256,  484,  256}, //31
    { 976,  516,  976,  516,  464,  244,  464,  244}, //32
    { 960,  504,  960,  504,  448,  236,  448,  236}, //33
    { 948,  500,  948,  500,  436,  228,  436,  228}, //34
    { 932,  492,  932,  492,  420,  220,  420,  220}, //35
    { 916,  484,  916,  484,  404,  216,  404,  216}, //36
    { 904,  476,  904,  476,  392,  208,  392,  208}, //37
    { 892,  468,  892,  468,  380,  200,  380,  200}, //38
    { 876,  460,  876,  460,  364,  192,  364,  192}, //39
    { 864,  456,  864,  456,  352,  188,  352,  188}, //40
    { 852,  448,  852,  448,  340,  180,  340,  180}, //41
    { 840,  444,  840,  444,  328,  172,  328,  172}, //42
    { 832,  440,  832,  440,  320,  168,  320,  168}, //43
    { 820,  432,  820,  432,  308,  164,  308,  164}, //44
    { 808,  424,  808,  424,  296,  156,  296,  156}, //45
    { 800,  420,  800,  420,  288,  152,  288,  152}, //46
    { 788,  416,  788,  416,  276,  148,  276,  148}, //47
    { 780,  412,  780,  412,  268,  140,  268,  140}, //48
    { 772,  408,  772,  408,  260,  136,  260,  136}, //49
    { 760,  400,  760,  400,  248,  132,  248,  132}, //50
    { 752,  396,  752,  396,  240,  128,  240,  128}, //51
    { 744,  392,  744,  392,  232,  124,  232,  124}, //52
    { 736,  388,  736,  388,  224,  120,  224,  120}, //53
    { 728,  384,  728,  384,  216,  116,  216,  116}, //54
    { 720,  380,  720,  380,  208,  112,  208,  112}, //55
    { 716,  376,  716,  376,  204,  108,  204,  108}, //56
    { 708,  372,  708,  372,  196,  104,  196,  104}, //57
    { 700,  368,  700,  368,  188,  100,  188,  100}, //58
    { 696,  368,  696,  368,  184,   96,  184,   96}, //59
    { 688,  364,  688,  364,  176,   92,  176,   92}, //60
    { 684,  360,  684,  360,  172,   88,  172,   88}, //61
};

const UINT32 VDOZOOM_INFOR_MODE_5_TABLE[61][DZOOM_ITEM_MAX] = {
    {1024,  768, 1024,  768, 1024,  768, 1024,  768}, //1

    {2560, 1440, 2560, 1440, 2472, 1392, 2472, 1392}, //2
    {2560, 1440, 2560, 1440, 2388, 1344, 2388, 1344}, //3
    {2560, 1440, 2560, 1440, 2308, 1296, 2308, 1296}, //4
    {2560, 1440, 2560, 1440, 2228, 1252, 2228, 1252}, //5
    {2560, 1440, 2560, 1440, 2152, 1212, 2152, 1212}, //6
    {2560, 1440, 2560, 1440, 2080, 1168, 2080, 1168}, //7
    {2560, 1440, 2560, 1440, 2008, 1128, 2008, 1128}, //8
    {2560, 1440, 2560, 1440, 1940, 1092, 1940, 1092}, //9
    {2560, 1440, 2560, 1440, 1876, 1056, 1876, 1056}, //10
    {2560, 1440, 2560, 1440, 1812, 1020, 1812, 1020}, //11
    {2560, 1440, 2560, 1440, 1748,  984, 1748,  984}, //12
    {2560, 1440, 2560, 1440, 1688,  952, 1688,  952}, //13
    {2560, 1440, 2560, 1440, 1632,  916, 1632,  916}, //14
    {2560, 1440, 2560, 1440, 1576,  888, 1576,  888}, //15
    {2552, 1436, 2552, 1436, 1524,  856, 1524,  856}, //16
    {2528, 1420, 2528, 1420, 1472,  828, 1472,  828}, //17
    {2500, 1408, 2500, 1408, 1420,  800, 1420,  800}, //18
    {2476, 1392, 2476, 1392, 1372,  772, 1372,  772}, //19
    {2452, 1380, 2452, 1380, 1324,  744, 1324,  744}, //20
    {1792, 1008, 1792, 1008, 1280,  720, 1280,  720}, //21
    {1748,  984, 1748,  984, 1236,  696, 1236,  696}, //22
    {1708,  960, 1708,  960, 1196,  672, 1196,  672}, //23
    {1664,  936, 1664,  936, 1152,  648, 1152,  648}, //24
    {1628,  916, 1628,  916, 1116,  628, 1116,  628}, //25
    {1588,  892, 1588,  892, 1076,  604, 1076,  604}, //26
    {1552,  872, 1552,  872, 1040,  584, 1040,  584}, //27
    {1516,  852, 1516,  852, 1004,  564, 1004,  564}, //28
    {1484,  832, 1484,  832,  972,  544,  972,  544}, //29
    {1448,  812, 1448,  812,  936,  528,  936,  528}, //30
    {1416,  796, 1416,  796,  904,  508,  904,  508}, //31
    {1388,  780, 1388,  780,  876,  492,  876,  492}, //32
    {1356,  760, 1356,  760,  844,  476,  844,  476}, //33
    {1328,  744, 1328,  744,  816,  460,  816,  460}, //34
    {1300,  732, 1300,  732,  788,  444,  788,  444}, //35
    {1272,  716, 1272,  716,  760,  428,  760,  428}, //36
    {1248,  700, 1248,  700,  736,  412,  736,  412}, //37
    {1224,  688, 1224,  688,  712,  400,  712,  400}, //38
    {1196,  672, 1196,  672,  684,  384,  684,  384}, //39
    {1176,  660, 1176,  660,  664,  372,  664,  372}, //40
    {1152,  648, 1152,  648,  640,  360,  640,  360}, //41
    {1132,  636, 1132,  636,  620,  348,  620,  348}, //42
    {1108,  624, 1108,  624,  596,  336,  596,  336}, //43
    {1088,  612, 1088,  612,  576,  324,  576,  324}, //44
    {1068,  600, 1068,  600,  556,  312,  556,  312}, //45
    {1052,  592, 1052,  592,  540,  304,  540,  304}, //46
    {1032,  580, 1032,  580,  520,  292,  520,  292}, //47
    {1016,  572, 1016,  572,  504,  284,  504,  284}, //48
    { 996,  560,  996,  560,  484,  272,  484,  272}, //49
    { 980,  552,  980,  552,  468,  264,  468,  264}, //50
    { 964,  540,  964,  540,  452,  256,  452,  256}, //51
    { 948,  532,  948,  532,  436,  244,  436,  244}, //52
    { 936,  524,  936,  524,  424,  236,  424,  236}, //53
    { 920,  516,  920,  516,  408,  228,  408,  228}, //54
    { 904,  508,  904,  508,  392,  220,  392,  220}, //55
    { 892,  500,  892,  500,  380,  216,  380,  216}, //56
    { 880,  492,  880,  492,  368,  208,  368,  208}, //57
    { 868,  488,  868,  488,  356,  200,  356,  200}, //58
    { 856,  480,  856,  480,  344,  192,  344,  192}, //59
    { 844,  472,  844,  472,  332,  188,  332,  188}, //60
    { 832,  468,  832,  468,  320,  180,  320,  180}, //61
};

const UINT32 VDOZOOM_INFOR_MODE_6_TABLE[61][DZOOM_ITEM_MAX] = {
    {1280,  720, 1280,  720, 1280,  720, 1280,  720}, //1

    {2560, 1440, 2560, 1440, 2472, 1392, 2472, 1392}, //2
    {2560, 1440, 2560, 1440, 2388, 1344, 2388, 1344}, //3
    {2560, 1440, 2560, 1440, 2308, 1296, 2308, 1296}, //4
    {2560, 1440, 2560, 1440, 2228, 1252, 2228, 1252}, //5
    {2560, 1440, 2560, 1440, 2152, 1212, 2152, 1212}, //6
    {2560, 1440, 2560, 1440, 2080, 1168, 2080, 1168}, //7
    {2560, 1440, 2560, 1440, 2008, 1128, 2008, 1128}, //8
    {2560, 1440, 2560, 1440, 1940, 1092, 1940, 1092}, //9
    {2560, 1440, 2560, 1440, 1876, 1056, 1876, 1056}, //10
    {2560, 1440, 2560, 1440, 1812, 1020, 1812, 1020}, //11
    {2560, 1440, 2560, 1440, 1748,  984, 1748,  984}, //12
    {2560, 1440, 2560, 1440, 1688,  952, 1688,  952}, //13
    {2560, 1440, 2560, 1440, 1632,  916, 1632,  916}, //14
    {2560, 1440, 2560, 1440, 1576,  888, 1576,  888}, //15
    {2552, 1436, 2552, 1436, 1524,  856, 1524,  856}, //16
    {2528, 1420, 2528, 1420, 1472,  828, 1472,  828}, //17
    {2500, 1408, 2500, 1408, 1420,  800, 1420,  800}, //18
    {2476, 1392, 2476, 1392, 1372,  772, 1372,  772}, //19
    {2452, 1380, 2452, 1380, 1324,  744, 1324,  744}, //20
    {1792, 1008, 1792, 1008, 1280,  720, 1280,  720}, //21
    {1748,  984, 1748,  984, 1236,  696, 1236,  696}, //22
    {1708,  960, 1708,  960, 1196,  672, 1196,  672}, //23
    {1664,  936, 1664,  936, 1152,  648, 1152,  648}, //24
    {1628,  916, 1628,  916, 1116,  628, 1116,  628}, //25
    {1588,  892, 1588,  892, 1076,  604, 1076,  604}, //26
    {1552,  872, 1552,  872, 1040,  584, 1040,  584}, //27
    {1516,  852, 1516,  852, 1004,  564, 1004,  564}, //28
    {1484,  832, 1484,  832,  972,  544,  972,  544}, //29
    {1448,  812, 1448,  812,  936,  528,  936,  528}, //30
    {1416,  796, 1416,  796,  904,  508,  904,  508}, //31
    {1388,  780, 1388,  780,  876,  492,  876,  492}, //32
    {1356,  760, 1356,  760,  844,  476,  844,  476}, //33
    {1328,  744, 1328,  744,  816,  460,  816,  460}, //34
    {1300,  732, 1300,  732,  788,  444,  788,  444}, //35
    {1272,  716, 1272,  716,  760,  428,  760,  428}, //36
    {1248,  700, 1248,  700,  736,  412,  736,  412}, //37
    {1224,  688, 1224,  688,  712,  400,  712,  400}, //38
    {1196,  672, 1196,  672,  684,  384,  684,  384}, //39
    {1176,  660, 1176,  660,  664,  372,  664,  372}, //40
    {1152,  648, 1152,  648,  640,  360,  640,  360}, //41
    {1132,  636, 1132,  636,  620,  348,  620,  348}, //42
    {1108,  624, 1108,  624,  596,  336,  596,  336}, //43
    {1088,  612, 1088,  612,  576,  324,  576,  324}, //44
    {1068,  600, 1068,  600,  556,  312,  556,  312}, //45
    {1052,  592, 1052,  592,  540,  304,  540,  304}, //46
    {1032,  580, 1032,  580,  520,  292,  520,  292}, //47
    {1016,  572, 1016,  572,  504,  284,  504,  284}, //48
    { 996,  560,  996,  560,  484,  272,  484,  272}, //49
    { 980,  552,  980,  552,  468,  264,  468,  264}, //50
    { 964,  540,  964,  540,  452,  256,  452,  256}, //51
    { 948,  532,  948,  532,  436,  244,  436,  244}, //52
    { 936,  524,  936,  524,  424,  236,  424,  236}, //53
    { 920,  516,  920,  516,  408,  228,  408,  228}, //54
    { 904,  508,  904,  508,  392,  220,  392,  220}, //55
    { 892,  500,  892,  500,  380,  216,  380,  216}, //56
    { 880,  492,  880,  492,  368,  208,  368,  208}, //57
    { 868,  488,  868,  488,  356,  200,  356,  200}, //58
    { 856,  480,  856,  480,  344,  192,  344,  192}, //59
    { 844,  472,  844,  472,  332,  188,  332,  188}, //60
    { 832,  468,  832,  468,  320,  180,  320,  180}, //61
};

const UINT32 VDOZOOM_INFOR_MODE_7_TABLE[61][DZOOM_ITEM_MAX] = {
    {1920,  1440, 1920,  1440, 1920,  1440, 1920,  1440}, //1

    {2560, 1440, 2560, 1440, 2472, 1392, 2472, 1392}, //2
    {2560, 1440, 2560, 1440, 2388, 1344, 2388, 1344}, //3
    {2560, 1440, 2560, 1440, 2308, 1296, 2308, 1296}, //4
    {2560, 1440, 2560, 1440, 2228, 1252, 2228, 1252}, //5
    {2560, 1440, 2560, 1440, 2152, 1212, 2152, 1212}, //6
    {2560, 1440, 2560, 1440, 2080, 1168, 2080, 1168}, //7
    {2560, 1440, 2560, 1440, 2008, 1128, 2008, 1128}, //8
    {2560, 1440, 2560, 1440, 1940, 1092, 1940, 1092}, //9
    {2560, 1440, 2560, 1440, 1876, 1056, 1876, 1056}, //10
    {2560, 1440, 2560, 1440, 1812, 1020, 1812, 1020}, //11
    {2560, 1440, 2560, 1440, 1748,  984, 1748,  984}, //12
    {2560, 1440, 2560, 1440, 1688,  952, 1688,  952}, //13
    {2560, 1440, 2560, 1440, 1632,  916, 1632,  916}, //14
    {2560, 1440, 2560, 1440, 1576,  888, 1576,  888}, //15
    {2552, 1436, 2552, 1436, 1524,  856, 1524,  856}, //16
    {2528, 1420, 2528, 1420, 1472,  828, 1472,  828}, //17
    {2500, 1408, 2500, 1408, 1420,  800, 1420,  800}, //18
    {2476, 1392, 2476, 1392, 1372,  772, 1372,  772}, //19
    {2452, 1380, 2452, 1380, 1324,  744, 1324,  744}, //20
    {1792, 1008, 1792, 1008, 1280,  720, 1280,  720}, //21
    {1748,  984, 1748,  984, 1236,  696, 1236,  696}, //22
    {1708,  960, 1708,  960, 1196,  672, 1196,  672}, //23
    {1664,  936, 1664,  936, 1152,  648, 1152,  648}, //24
    {1628,  916, 1628,  916, 1116,  628, 1116,  628}, //25
    {1588,  892, 1588,  892, 1076,  604, 1076,  604}, //26
    {1552,  872, 1552,  872, 1040,  584, 1040,  584}, //27
    {1516,  852, 1516,  852, 1004,  564, 1004,  564}, //28
    {1484,  832, 1484,  832,  972,  544,  972,  544}, //29
    {1448,  812, 1448,  812,  936,  528,  936,  528}, //30
    {1416,  796, 1416,  796,  904,  508,  904,  508}, //31
    {1388,  780, 1388,  780,  876,  492,  876,  492}, //32
    {1356,  760, 1356,  760,  844,  476,  844,  476}, //33
    {1328,  744, 1328,  744,  816,  460,  816,  460}, //34
    {1300,  732, 1300,  732,  788,  444,  788,  444}, //35
    {1272,  716, 1272,  716,  760,  428,  760,  428}, //36
    {1248,  700, 1248,  700,  736,  412,  736,  412}, //37
    {1224,  688, 1224,  688,  712,  400,  712,  400}, //38
    {1196,  672, 1196,  672,  684,  384,  684,  384}, //39
    {1176,  660, 1176,  660,  664,  372,  664,  372}, //40
    {1152,  648, 1152,  648,  640,  360,  640,  360}, //41
    {1132,  636, 1132,  636,  620,  348,  620,  348}, //42
    {1108,  624, 1108,  624,  596,  336,  596,  336}, //43
    {1088,  612, 1088,  612,  576,  324,  576,  324}, //44
    {1068,  600, 1068,  600,  556,  312,  556,  312}, //45
    {1052,  592, 1052,  592,  540,  304,  540,  304}, //46
    {1032,  580, 1032,  580,  520,  292,  520,  292}, //47
    {1016,  572, 1016,  572,  504,  284,  504,  284}, //48
    { 996,  560,  996,  560,  484,  272,  484,  272}, //49
    { 980,  552,  980,  552,  468,  264,  468,  264}, //50
    { 964,  540,  964,  540,  452,  256,  452,  256}, //51
    { 948,  532,  948,  532,  436,  244,  436,  244}, //52
    { 936,  524,  936,  524,  424,  236,  424,  236}, //53
    { 920,  516,  920,  516,  408,  228,  408,  228}, //54
    { 904,  508,  904,  508,  392,  220,  392,  220}, //55
    { 892,  500,  892,  500,  380,  216,  380,  216}, //56
    { 880,  492,  880,  492,  368,  208,  368,  208}, //57
    { 868,  488,  868,  488,  356,  200,  356,  200}, //58
    { 856,  480,  856,  480,  344,  192,  344,  192}, //59
    { 844,  472,  844,  472,  332,  188,  332,  188}, //60
    { 832,  468,  832,  468,  320,  180,  320,  180}, //61
};

UINT32 *SenMode2TblFp_ov12895m_evb(UINT32 id, UINT32 *DzMaxidx)
{
	UINT32 *Ptr = NULL;
	UINT32 tbl_size,i;
	UINT32 img_size_h, img_size_v;
	
	ER rt = E_OK;
	SEN_STATUS_PARAM sen_status = {0};
	UINT32 sen_mode;

	sen_mode = IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE);
	sen_status.sensor_mode = IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE);
	rt = sensor_get_info(IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)), SEN_GET_STATUS, (void *)&sen_status);
	if (rt != E_OK) {
		DBG_ERR("Get Sensor Status Fail id:%d, Sensor_Mode: %d\r\n", IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE));
		return NULL;
	}
	
    img_size_h = (IPL_AlgGetUIInfo(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_SEL_VIDEO_SIZE) & 0xffff0000) >> 16;
	img_size_v = (IPL_AlgGetUIInfo(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_SEL_VIDEO_SIZE) & 0x0000ffff);
	
	//special case for manual select dzoom table
	switch (sen_mode) {
	case SENSOR_MODE_1:
		Ptr = NULL;
		*DzMaxidx = 0;
        Ptr = (UINT32 *)&VDOZOOM_INFOR_MODE_1_TABLE[0][0];
        *DzMaxidx = (sizeof(VDOZOOM_INFOR_MODE_1_TABLE) / 4 / DZOOM_ITEM_MAX) - 1;
		break;

	case SENSOR_MODE_2:
		Ptr = NULL;
		*DzMaxidx = 0;

        if((img_size_h==1920)&&(img_size_v==1080)) {
            Ptr = (UINT32 *)&VDOZOOM_INFOR_MODE_2_TABLE_1920x1080[0][0];
            *DzMaxidx = (sizeof(VDOZOOM_INFOR_MODE_2_TABLE_1920x1080) / 4 / DZOOM_ITEM_MAX) - 1;
        } else {
            Ptr = (UINT32 *)&VDOZOOM_INFOR_MODE_2_TABLE[0][0];
            *DzMaxidx = (sizeof(VDOZOOM_INFOR_MODE_2_TABLE) / 4 / DZOOM_ITEM_MAX) - 1;
        }
		break;

    case SENSOR_MODE_3:
        Ptr = NULL;
        *DzMaxidx = 0;
        Ptr = (UINT32 *)&VDOZOOM_INFOR_MODE_3_TABLE[0][0];
        *DzMaxidx = (sizeof(VDOZOOM_INFOR_MODE_3_TABLE) / 4 / DZOOM_ITEM_MAX) - 1;
        break;

    case SENSOR_MODE_4:
        Ptr = NULL;
        *DzMaxidx = 0;
        Ptr = (UINT32 *)&VDOZOOM_INFOR_MODE_4_TABLE[0][0];
        *DzMaxidx = (sizeof(VDOZOOM_INFOR_MODE_4_TABLE) / 4 / DZOOM_ITEM_MAX) - 1;
        break;

    case SENSOR_MODE_5:
        Ptr = NULL;
        *DzMaxidx = 0;
        Ptr = (UINT32 *)&VDOZOOM_INFOR_MODE_5_TABLE[0][0];
        *DzMaxidx = (sizeof(VDOZOOM_INFOR_MODE_5_TABLE) / 4 / DZOOM_ITEM_MAX) - 1;
        break;

    case SENSOR_MODE_6:
        Ptr = NULL;
        *DzMaxidx = 0;
        Ptr = (UINT32 *)&VDOZOOM_INFOR_MODE_6_TABLE[0][0];
        *DzMaxidx = (sizeof(VDOZOOM_INFOR_MODE_6_TABLE) / 4 / DZOOM_ITEM_MAX) - 1;
        break;

    case SENSOR_MODE_7:
        Ptr = NULL;
        *DzMaxidx = 0;
        Ptr = (UINT32 *)&VDOZOOM_INFOR_MODE_7_TABLE[0][0];
        *DzMaxidx = (sizeof(VDOZOOM_INFOR_MODE_7_TABLE) / 4 / DZOOM_ITEM_MAX) - 1;
        break;

	default:
		Ptr = NULL;
		*DzMaxidx = 0;
		break;
	}

	tbl_size = sizeof(sensor_mode_dzoom_table) / sizeof(IPL_DZOOM_SEL_INFO);
	//auto gen dzoom table
	if(tbl_size == 0){
		//use default setting
		Ptr = ChkSenModeTbl(id, &sen_status.sensor_info, Ptr, DzMaxidx, NULL);
	} else {
		for(i=0;i<tbl_size;i++){
			if(sensor_mode_dzoom_table[i].mode == sen_mode){
				Ptr = ChkSenModeTbl(id, &sen_status.sensor_info, Ptr, DzMaxidx, &sensor_mode_dzoom_table[i]);
			} else {
				//use default setting
				Ptr = ChkSenModeTbl(id, &sen_status.sensor_info, Ptr, DzMaxidx, NULL);
			}
		}
	}
	return Ptr;
}