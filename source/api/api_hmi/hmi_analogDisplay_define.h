///*****************************************////
//  Name : hmi_analogDisplay_define.h
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#ifndef _HMI_ANALOGDISPLAY_DEFINE_H_
#define _HMI_ANALOGDISPLAY_DEFINE_H_

#define AD_HMI_ADISP_TESTDATA    0
#define AD_MCTRLDATA_FTEMP       1

#define AD_MCTRLDATA_FIU         10
#define AD_MCTRLDATA_FIV         11
#define AD_MCTRLDATA_FIW         12
#define AD_MCTRLDATA_FIALPHA     13
#define AD_MCTRLDATA_FIBETA      14
#define AD_MCTRLDATA_FID         15
#define AD_MCTRLDATA_FIQ         16

#define AD_MCTRLDATA_FVD         20
#define AD_MCTRLDATA_FVQ         21
#define AD_MCTRLDATA_FVALPHA     22
#define AD_MCTRLDATA_FVBETA      23
#define AD_MCTRLDATA_FVU         24
#define AD_MCTRLDATA_FVV         25
#define AD_MCTRLDATA_FVW         26

#define AD_MCTRLDATA_FTA         30
#define AD_MCTRLDATA_FTB         31
#define AD_MCTRLDATA_FTC         32

#define AD_MCTRLDATA_FV          40

#define AD_MCTRLDATA_FP          50

#define AD_MCTRLDATA_FAANGLEVIRTUAL     60
#define AD_MCTRLDATA_FANGLEMECH  		61
#define AD_MCTRLDATA_FANGLEELEC  		62
#define AD_MCTRLDATA_UVWINDEX  		    63

#define AD_MCTRL_FPLOOPMAXV      103
#define AD_MCTRL_FPLOOPMINV      104
#define AD_MCTRL_FPOUT           105

#define AD_MCTRL_FVCMD           110
#define AD_MCTRL_FVCMDPARA       111
#define AD_MCTRL_FVFBK           112
#define AD_MCTRL_FVLOOPMAXI      113
#define AD_MCTRL_FVLOOPMINI      114
#define AD_MCTRL_FVOUT           115

#define AD_MCTRL_FIQCMD          120
#define AD_MCTRL_FIQCMDPARA      121
#define AD_MCTRL_FIQFBK          122
#define AD_MCTRL_FIQLOOPMAXVQ    123
#define AD_MCTRL_FIQLOOPMINVQ    124
#define AD_MCTRL_FIQOUT          125

#define AD_MCTRL_FIDCMD          130
#define AD_MCTRL_FIDCMDPARA      131
#define AD_MCTRL_FIDFBK          132
#define AD_MCTRL_FIDLOOPMAXVD    133
#define AD_MCTRL_FIDLOOPMINVD    134
#define AD_MCTRL_FIDOUT          135

#define AD_MCTRL_PARK_FALPHA     150
#define AD_MCTRL_PARK_FBETA      151
#define AD_MCTRL_PARK_FTHETA     152
#define AD_MCTRL_PARK_FSINE      153
#define AD_MCTRL_PARK_FCOSINE    154
#define AD_MCTRL_PARK_FD         155
#define AD_MCTRL_PARK_FQ         156

#define AD_MCTRL_IPARK_FALPHA    160
#define AD_MCTRL_IPARK_FBETA     161
#define AD_MCTRL_IPARK_FTHETA    162
#define AD_MCTRL_IPARK_FSINE     163
#define AD_MCTRL_IPARK_FCOSINE   164
#define AD_MCTRL_IPARK_FD        165
#define AD_MCTRL_IPARK_FQ        166

#define AD_MCTRL_CLARKE_FU       170
#define AD_MCTRL_CLARKE_FV       171
#define AD_MCTRL_CLARKE_FW       172
#define AD_MCTRL_CLARKE_FALPHA   173
#define AD_MCTRL_CLARKE_FBETA    174

#define AD_MCTRL_ICLARKE_FU      180
#define AD_MCTRL_ICLARKE_FV      181
#define AD_MCTRL_ICLARKE_FW      182
#define AD_MCTRL_ICLARKE_FALPHA  183
#define AD_MCTRL_ICLARKE_FBETA   184

#define AD_MCTRL_SVM_FU          190
#define AD_MCTRL_SVM_FV          191
#define AD_MCTRL_SVM_FW          192
#define AD_MCTRL_SVM_FA          193
#define AD_MCTRL_SVM_FB          194
#define AD_MCTRL_SVM_FC          195

#define AD_MCTRL_IQ_PI_FREF      200
#define AD_MCTRL_IQ_PI_FFBK      201
#define AD_MCTRL_IQ_PI_FERR      202
#define AD_MCTRL_IQ_PI_FUP       203
#define AD_MCTRL_IQ_PI_FINT      204
#define AD_MCTRL_IQ_PI_FUI       205
#define AD_MCTRL_IQ_PI_FMAX      206
#define AD_MCTRL_IQ_PI_FMIN      207
#define AD_MCTRL_IQ_PI_FOUTSAT   208
#define AD_MCTRL_IQ_PI_FOUT      209

#define AD_MCTRL_ID_PI_FREF      210
#define AD_MCTRL_ID_PI_FFBK      211
#define AD_MCTRL_ID_PI_FERR      212
#define AD_MCTRL_ID_PI_FUP       213
#define AD_MCTRL_ID_PI_FINT      214
#define AD_MCTRL_ID_PI_FUI       215
#define AD_MCTRL_ID_PI_FMAX      216
#define AD_MCTRL_ID_PI_FMIN      217
#define AD_MCTRL_ID_PI_FOUTSAT   218
#define AD_MCTRL_ID_PI_FOUT      219

#define AD_MCTRL_V_PI_FREF       220
#define AD_MCTRL_V_PI_FFBK       221
#define AD_MCTRL_V_PI_FERR       222
#define AD_MCTRL_V_PI_FUP        223
#define AD_MCTRL_V_PI_FINT       224
#define AD_MCTRL_V_PI_FUI        225
#define AD_MCTRL_V_PI_FMAX       226
#define AD_MCTRL_V_PI_FMIN       227
#define AD_MCTRL_V_PI_FOUTSAT    228
#define AD_MCTRL_V_PI_FOUT       229

#define AD_MCTRL_P_P_FREF        230
#define AD_MCTRL_P_P_FFBK        231
#define AD_MCTRL_P_P_FERR        232
#define AD_MCTRL_P_P_FUP         233
#define AD_MCTRL_P_P_FMAX        234
#define AD_MCTRL_P_P_FMIN        235
#define AD_MCTRL_P_P_FOUTSAT     236
#define AD_MCTRL_P_P_FOUT        237


#endif // end of file
