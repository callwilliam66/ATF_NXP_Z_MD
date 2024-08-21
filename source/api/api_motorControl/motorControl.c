////*****************************************////
//  Name : motorControl.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "motorControl.h"

MOTOR_CONTROL_REGS mCtrlRegs;

void mCtrl_init(void)
{
	mCtrl_uart_init(&mCtrlRegs.uart1Regs,LPUART1_PERIPHERAL);
	mCtrl_uart_init(&mCtrlRegs.uart2Regs,LPUART3_PERIPHERAL);
	mCtrl_uart_init(&mCtrlRegs.uart3Regs,LPUART4_PERIPHERAL);


	mCtrlRegs.emgRegs.ulEmgState = 0;
	mCtrlRegs.emgRegs.ulEmgStateIO = 0;
	mCtrlRegs.emgRegs.ulEmgStateSW = 0;

	mCtrlRegs.uartRxCmd[0] = uartPacketCmd0;
	mCtrlRegs.uartRxCmd[1] = uartPacketCmd1;
	mCtrlRegs.uartRxCmd[2] = uartPacketCmd2;
	mCtrlRegs.uartRxCmd[3] = uartPacketCmd3;
	mCtrlRegs.uartRxCmd[4] = uartPacketCmd4;
	mCtrlRegs.uartRxCmd[5] = uartPacketCmd5;
	mCtrlRegs.uartRxCmd[6] = uartPacketCmd6;
	mCtrlRegs.uartRxCmd[7] = uartPacketCmd7;
	mCtrlRegs.uartRxCmd[8] = uartPacketCmd8;
	mCtrlRegs.uartRxCmd[9] = uartPacketCmd9;
	mCtrlRegs.uartRxCmd[10] = uartPacketCmd10;
	mCtrlRegs.uartRxCmd[11] = uartPacketCmd11;
	mCtrlRegs.uartRxCmd[12] = uartPacketCmd12;
	mCtrlRegs.uartRxCmd[13] = uartPacketCmd13;
	mCtrlRegs.uartRxCmd[14] = uartPacketCmd14;
	mCtrlRegs.uartRxCmd[15] = uartPacketCmd15;
	mCtrlRegs.uartRxCmd[16] = uartPacketCmd16;
	mCtrlRegs.uartRxCmd[17] = uartPacketCmd17;
	mCtrlRegs.uartRxCmd[18] = uartPacketCmd18;
	mCtrlRegs.uartRxCmd[19] = uartPacketCmd19;
	mCtrlRegs.uartRxCmd[20] = uartPacketCmd20;
	mCtrlRegs.uartRxCmd[21] = uartPacketCmd21;
	mCtrlRegs.uartRxCmd[22] = uartPacketCmd22;
	mCtrlRegs.uartRxCmd[23] = uartPacketCmd23;
	mCtrlRegs.uartRxCmd[24] = uartPacketCmd24;
	mCtrlRegs.uartRxCmd[25] = uartPacketCmd25;
	mCtrlRegs.uartRxCmd[26] = uartPacketCmd26;
	mCtrlRegs.uartRxCmd[27] = uartPacketCmd27;
	mCtrlRegs.uartRxCmd[28] = uartPacketCmd28;
	mCtrlRegs.uartRxCmd[29] = uartPacketCmd29;
	mCtrlRegs.uartRxCmd[30] = uartPacketCmd30;
	mCtrlRegs.uartRxCmd[31] = uartPacketCmd31;
	mCtrlRegs.uartRxCmd[32] = uartPacketCmd32;
	mCtrlRegs.uartRxCmd[33] = uartPacketCmd33;
	mCtrlRegs.uartRxCmd[34] = uartPacketCmd34;
	mCtrlRegs.uartRxCmd[35] = uartPacketCmd35;
	mCtrlRegs.uartRxCmd[36] = uartPacketCmd36;
	mCtrlRegs.uartRxCmd[37] = uartPacketCmd37;
	mCtrlRegs.uartRxCmd[38] = uartPacketCmd38;
	mCtrlRegs.uartRxCmd[39] = uartPacketCmd39;
	mCtrlRegs.uartRxCmd[40] = uartPacketCmd40;
	mCtrlRegs.uartRxCmd[41] = uartPacketCmd41;
	mCtrlRegs.uartRxCmd[42] = uartPacketCmd42;
	mCtrlRegs.uartRxCmd[43] = uartPacketCmd43;
	mCtrlRegs.uartRxCmd[44] = uartPacketCmd44;
	mCtrlRegs.uartRxCmd[45] = uartPacketCmd45;
	mCtrlRegs.uartRxCmd[46] = uartPacketCmd46;
	mCtrlRegs.uartRxCmd[47] = uartPacketCmd47;
	mCtrlRegs.uartRxCmd[48] = uartPacketCmd48;
	mCtrlRegs.uartRxCmd[49] = uartPacketCmd49;
	mCtrlRegs.uartRxCmd[50] = uartPacketCmd50;
	mCtrlRegs.uartRxCmd[51] = uartPacketCmd51;
	mCtrlRegs.uartRxCmd[52] = uartPacketCmd52;
	mCtrlRegs.uartRxCmd[53] = uartPacketCmd53;
	mCtrlRegs.uartRxCmd[54] = uartPacketCmd54;
	mCtrlRegs.uartRxCmd[55] = uartPacketCmd55;
	mCtrlRegs.uartRxCmd[56] = uartPacketCmd56;
	mCtrlRegs.uartRxCmd[57] = uartPacketCmd57;
	mCtrlRegs.uartRxCmd[58] = uartPacketCmd58;
	mCtrlRegs.uartRxCmd[59] = uartPacketCmd59;
	mCtrlRegs.uartRxCmd[60] = uartPacketCmd60;
	mCtrlRegs.uartRxCmd[61] = uartPacketCmd61;
	mCtrlRegs.uartRxCmd[62] = uartPacketCmd62;
	mCtrlRegs.uartRxCmd[63] = uartPacketCmd63;
	mCtrlRegs.uartRxCmd[64] = uartPacketCmd64;
	mCtrlRegs.uartRxCmd[65] = uartPacketCmd65;
	mCtrlRegs.uartRxCmd[66] = uartPacketCmd66;
	mCtrlRegs.uartRxCmd[67] = uartPacketCmd67;
	mCtrlRegs.uartRxCmd[68] = uartPacketCmd68;
	mCtrlRegs.uartRxCmd[69] = uartPacketCmd69;
	mCtrlRegs.uartRxCmd[70] = uartPacketCmd70;
	mCtrlRegs.uartRxCmd[71] = uartPacketCmd71;
	mCtrlRegs.uartRxCmd[72] = uartPacketCmd72;
	mCtrlRegs.uartRxCmd[73] = uartPacketCmd73;
	mCtrlRegs.uartRxCmd[74] = uartPacketCmd74;
	mCtrlRegs.uartRxCmd[75] = uartPacketCmd75;
	mCtrlRegs.uartRxCmd[76] = uartPacketCmd76;
	mCtrlRegs.uartRxCmd[77] = uartPacketCmd77;
	mCtrlRegs.uartRxCmd[78] = uartPacketCmd78;
	mCtrlRegs.uartRxCmd[79] = uartPacketCmd79;
	mCtrlRegs.uartRxCmd[80] = uartPacketCmd80;
	mCtrlRegs.uartRxCmd[81] = uartPacketCmd81;
	mCtrlRegs.uartRxCmd[82] = uartPacketCmd82;
	mCtrlRegs.uartRxCmd[83] = uartPacketCmd83;
	mCtrlRegs.uartRxCmd[84] = uartPacketCmd84;
	mCtrlRegs.uartRxCmd[85] = uartPacketCmd85;
	mCtrlRegs.uartRxCmd[86] = uartPacketCmd86;
	mCtrlRegs.uartRxCmd[87] = uartPacketCmd87;
	mCtrlRegs.uartRxCmd[88] = uartPacketCmd88;
	mCtrlRegs.uartRxCmd[89] = uartPacketCmd89;
	mCtrlRegs.uartRxCmd[90] = uartPacketCmd90;
	mCtrlRegs.uartRxCmd[91] = uartPacketCmd91;
	mCtrlRegs.uartRxCmd[92] = uartPacketCmd92;
	mCtrlRegs.uartRxCmd[93] = uartPacketCmd93;
	mCtrlRegs.uartRxCmd[94] = uartPacketCmd94;
	mCtrlRegs.uartRxCmd[95] = uartPacketCmd95;
	mCtrlRegs.uartRxCmd[96] = uartPacketCmd96;
	mCtrlRegs.uartRxCmd[97] = uartPacketCmd97;
	mCtrlRegs.uartRxCmd[98] = uartPacketCmd98;
	mCtrlRegs.uartRxCmd[99] = uartPacketCmd99;
	mCtrlRegs.uartRxCmd[100] = uartPacketCmd100;
	mCtrlRegs.uartRxCmd[101] = uartPacketCmd101;
	mCtrlRegs.uartRxCmd[102] = uartPacketCmd102;
	mCtrlRegs.uartRxCmd[103] = uartPacketCmd103;
	mCtrlRegs.uartRxCmd[104] = uartPacketCmd104;
	mCtrlRegs.uartRxCmd[105] = uartPacketCmd105;
	mCtrlRegs.uartRxCmd[106] = uartPacketCmd106;
	mCtrlRegs.uartRxCmd[107] = uartPacketCmd107;
	mCtrlRegs.uartRxCmd[108] = uartPacketCmd108;
	mCtrlRegs.uartRxCmd[109] = uartPacketCmd109;
	mCtrlRegs.uartRxCmd[110] = uartPacketCmd110;
	mCtrlRegs.uartRxCmd[111] = uartPacketCmd111;
	mCtrlRegs.uartRxCmd[112] = uartPacketCmd112;
	mCtrlRegs.uartRxCmd[113] = uartPacketCmd113;
	mCtrlRegs.uartRxCmd[114] = uartPacketCmd114;
	mCtrlRegs.uartRxCmd[115] = uartPacketCmd115;
	mCtrlRegs.uartRxCmd[116] = uartPacketCmd116;
	mCtrlRegs.uartRxCmd[117] = uartPacketCmd117;
	mCtrlRegs.uartRxCmd[118] = uartPacketCmd118;
	mCtrlRegs.uartRxCmd[119] = uartPacketCmd119;
	mCtrlRegs.uartRxCmd[120] = uartPacketCmd120;
	mCtrlRegs.uartRxCmd[121] = uartPacketCmd121;
	mCtrlRegs.uartRxCmd[122] = uartPacketCmd122;
	mCtrlRegs.uartRxCmd[123] = uartPacketCmd123;
	mCtrlRegs.uartRxCmd[124] = uartPacketCmd124;
	mCtrlRegs.uartRxCmd[125] = uartPacketCmd125;
	mCtrlRegs.uartRxCmd[126] = uartPacketCmd126;
	mCtrlRegs.uartRxCmd[127] = uartPacketCmd127;
	mCtrlRegs.uartRxCmd[128] = uartPacketCmd128;
	mCtrlRegs.uartRxCmd[129] = uartPacketCmd129;
	mCtrlRegs.uartRxCmd[130] = uartPacketCmd130;
	mCtrlRegs.uartRxCmd[131] = uartPacketCmd131;
	mCtrlRegs.uartRxCmd[132] = uartPacketCmd132;
	mCtrlRegs.uartRxCmd[133] = uartPacketCmd133;
	mCtrlRegs.uartRxCmd[134] = uartPacketCmd134;
	mCtrlRegs.uartRxCmd[135] = uartPacketCmd135;
	mCtrlRegs.uartRxCmd[136] = uartPacketCmd136;
	mCtrlRegs.uartRxCmd[137] = uartPacketCmd137;
	mCtrlRegs.uartRxCmd[138] = uartPacketCmd138;
	mCtrlRegs.uartRxCmd[139] = uartPacketCmd139;
	mCtrlRegs.uartRxCmd[140] = uartPacketCmd140;
	mCtrlRegs.uartRxCmd[141] = uartPacketCmd141;
	mCtrlRegs.uartRxCmd[142] = uartPacketCmd142;
	mCtrlRegs.uartRxCmd[143] = uartPacketCmd143;
	mCtrlRegs.uartRxCmd[144] = uartPacketCmd144;
	mCtrlRegs.uartRxCmd[145] = uartPacketCmd145;
	mCtrlRegs.uartRxCmd[146] = uartPacketCmd146;
	mCtrlRegs.uartRxCmd[147] = uartPacketCmd147;
	mCtrlRegs.uartRxCmd[148] = uartPacketCmd148;
	mCtrlRegs.uartRxCmd[149] = uartPacketCmd149;
	mCtrlRegs.uartRxCmd[150] = uartPacketCmd150;
	mCtrlRegs.uartRxCmd[151] = uartPacketCmd151;
	mCtrlRegs.uartRxCmd[152] = uartPacketCmd152;
	mCtrlRegs.uartRxCmd[153] = uartPacketCmd153;
	mCtrlRegs.uartRxCmd[154] = uartPacketCmd154;
	mCtrlRegs.uartRxCmd[155] = uartPacketCmd155;
	mCtrlRegs.uartRxCmd[156] = uartPacketCmd156;
	mCtrlRegs.uartRxCmd[157] = uartPacketCmd157;
	mCtrlRegs.uartRxCmd[158] = uartPacketCmd158;
	mCtrlRegs.uartRxCmd[159] = uartPacketCmd159;
	mCtrlRegs.uartRxCmd[160] = uartPacketCmd160;
	mCtrlRegs.uartRxCmd[161] = uartPacketCmd161;
	mCtrlRegs.uartRxCmd[162] = uartPacketCmd162;
	mCtrlRegs.uartRxCmd[163] = uartPacketCmd163;
	mCtrlRegs.uartRxCmd[164] = uartPacketCmd164;
	mCtrlRegs.uartRxCmd[165] = uartPacketCmd165;
	mCtrlRegs.uartRxCmd[166] = uartPacketCmd166;
	mCtrlRegs.uartRxCmd[167] = uartPacketCmd167;
	mCtrlRegs.uartRxCmd[168] = uartPacketCmd168;
	mCtrlRegs.uartRxCmd[169] = uartPacketCmd169;
	mCtrlRegs.uartRxCmd[170] = uartPacketCmd170;
	mCtrlRegs.uartRxCmd[171] = uartPacketCmd171;
	mCtrlRegs.uartRxCmd[172] = uartPacketCmd172;
	mCtrlRegs.uartRxCmd[173] = uartPacketCmd173;
	mCtrlRegs.uartRxCmd[174] = uartPacketCmd174;
	mCtrlRegs.uartRxCmd[175] = uartPacketCmd175;
	mCtrlRegs.uartRxCmd[176] = uartPacketCmd176;
	mCtrlRegs.uartRxCmd[177] = uartPacketCmd177;
	mCtrlRegs.uartRxCmd[178] = uartPacketCmd178;
	mCtrlRegs.uartRxCmd[179] = uartPacketCmd179;
	mCtrlRegs.uartRxCmd[180] = uartPacketCmd180;
	mCtrlRegs.uartRxCmd[181] = uartPacketCmd181;
	mCtrlRegs.uartRxCmd[182] = uartPacketCmd182;
	mCtrlRegs.uartRxCmd[183] = uartPacketCmd183;
	mCtrlRegs.uartRxCmd[184] = uartPacketCmd184;
	mCtrlRegs.uartRxCmd[185] = uartPacketCmd185;
	mCtrlRegs.uartRxCmd[186] = uartPacketCmd186;
	mCtrlRegs.uartRxCmd[187] = uartPacketCmd187;
	mCtrlRegs.uartRxCmd[188] = uartPacketCmd188;
	mCtrlRegs.uartRxCmd[189] = uartPacketCmd189;
	mCtrlRegs.uartRxCmd[190] = uartPacketCmd190;
	mCtrlRegs.uartRxCmd[191] = uartPacketCmd191;
	mCtrlRegs.uartRxCmd[192] = uartPacketCmd192;
	mCtrlRegs.uartRxCmd[193] = uartPacketCmd193;
	mCtrlRegs.uartRxCmd[194] = uartPacketCmd194;
	mCtrlRegs.uartRxCmd[195] = uartPacketCmd195;
	mCtrlRegs.uartRxCmd[196] = uartPacketCmd196;
	mCtrlRegs.uartRxCmd[197] = uartPacketCmd197;
	mCtrlRegs.uartRxCmd[198] = uartPacketCmd198;
	mCtrlRegs.uartRxCmd[199] = uartPacketCmd199;
	mCtrlRegs.uartRxCmd[200] = uartPacketCmd200;
	mCtrlRegs.uartRxCmd[201] = uartPacketCmd201;
	mCtrlRegs.uartRxCmd[202] = uartPacketCmd202;
	mCtrlRegs.uartRxCmd[203] = uartPacketCmd203;
	mCtrlRegs.uartRxCmd[204] = uartPacketCmd204;
	mCtrlRegs.uartRxCmd[205] = uartPacketCmd205;
	mCtrlRegs.uartRxCmd[206] = uartPacketCmd206;
	mCtrlRegs.uartRxCmd[207] = uartPacketCmd207;
	mCtrlRegs.uartRxCmd[208] = uartPacketCmd208;
	mCtrlRegs.uartRxCmd[209] = uartPacketCmd209;
	mCtrlRegs.uartRxCmd[210] = uartPacketCmd210;
	mCtrlRegs.uartRxCmd[211] = uartPacketCmd211;
	mCtrlRegs.uartRxCmd[212] = uartPacketCmd212;
	mCtrlRegs.uartRxCmd[213] = uartPacketCmd213;
	mCtrlRegs.uartRxCmd[214] = uartPacketCmd214;
	mCtrlRegs.uartRxCmd[215] = uartPacketCmd215;
	mCtrlRegs.uartRxCmd[216] = uartPacketCmd216;
	mCtrlRegs.uartRxCmd[217] = uartPacketCmd217;
	mCtrlRegs.uartRxCmd[218] = uartPacketCmd218;
	mCtrlRegs.uartRxCmd[219] = uartPacketCmd219;
	mCtrlRegs.uartRxCmd[220] = uartPacketCmd220;
	mCtrlRegs.uartRxCmd[221] = uartPacketCmd221;
	mCtrlRegs.uartRxCmd[222] = uartPacketCmd222;
	mCtrlRegs.uartRxCmd[223] = uartPacketCmd223;
	mCtrlRegs.uartRxCmd[224] = uartPacketCmd224;
	mCtrlRegs.uartRxCmd[225] = uartPacketCmd225;
	mCtrlRegs.uartRxCmd[226] = uartPacketCmd226;
	mCtrlRegs.uartRxCmd[227] = uartPacketCmd227;
	mCtrlRegs.uartRxCmd[228] = uartPacketCmd228;
	mCtrlRegs.uartRxCmd[229] = uartPacketCmd229;
	mCtrlRegs.uartRxCmd[230] = uartPacketCmd230;
	mCtrlRegs.uartRxCmd[231] = uartPacketCmd231;
	mCtrlRegs.uartRxCmd[232] = uartPacketCmd232;
	mCtrlRegs.uartRxCmd[233] = uartPacketCmd233;
	mCtrlRegs.uartRxCmd[234] = uartPacketCmd234;
	mCtrlRegs.uartRxCmd[235] = uartPacketCmd235;
	mCtrlRegs.uartRxCmd[236] = uartPacketCmd236;
	mCtrlRegs.uartRxCmd[237] = uartPacketCmd237;
	mCtrlRegs.uartRxCmd[238] = uartPacketCmd238;
	mCtrlRegs.uartRxCmd[239] = uartPacketCmd239;
	mCtrlRegs.uartRxCmd[240] = uartPacketCmd240;
	mCtrlRegs.uartRxCmd[241] = uartPacketCmd241;
	mCtrlRegs.uartRxCmd[242] = uartPacketCmd242;
	mCtrlRegs.uartRxCmd[243] = uartPacketCmd243;
	mCtrlRegs.uartRxCmd[244] = uartPacketCmd244;
	mCtrlRegs.uartRxCmd[245] = uartPacketCmd245;
	mCtrlRegs.uartRxCmd[246] = uartPacketCmd246;
	mCtrlRegs.uartRxCmd[247] = uartPacketCmd247;
	mCtrlRegs.uartRxCmd[248] = uartPacketCmd248;
	mCtrlRegs.uartRxCmd[249] = uartPacketCmd249;
	mCtrlRegs.uartRxCmd[250] = uartPacketCmd250;
	mCtrlRegs.uartRxCmd[251] = uartPacketCmd251;
	mCtrlRegs.uartRxCmd[252] = uartPacketCmd252;
	mCtrlRegs.uartRxCmd[253] = uartPacketCmd253;
	mCtrlRegs.uartRxCmd[254] = uartPacketCmd254;
	mCtrlRegs.uartRxCmd[255] = uartPacketCmd255;


}


