////*****************************************////
//  Name : parameter_default.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "parameter.h"

const char paraName_blank[]		    		= "0";
const char paraName_controlMode[]			= "controlMode";
const char paraName_servoOnMode[]			= "servoOnMode";
const char paraName_ctrlType[]				= "ctrlType";
const char paraName_driverInfo[]			= "driverInfo";
const char paraName_firmwareVer[]			= "firmwareVer";
const char paraName_homeEnable[]			= "homeEnable";
const char paraName_limitPosEna[]			= "limitPosEnable";
const char paraName_limitNegEna[]			= "limitNegEnable";
const char paraName_positionKp[]			= "positionKp";
const char paraName_positionKd[]			= "poistionKd";
const char paraName_positionCoefficient[]	= "positionCoefficient";

const char paraName_speedKp[]				= "speedKp";
const char paraName_speedKi[]				= "speedKi";

const char paraName_speedKf[]				= "speedKf";
const char paraName_speedRKf[]				= "speedRKf";

const char paraName_currentKp[]	    		= "currentKp";
const char paraName_currentKi[]	   			= "currentKi";
const char paraName_currentBw[]	    		= "currentBw";
const char paraName_currentTc[]	   			= "currentTc";

const char paraName_posCmdPara[]			= "posCmdPara";

const char paraName_spdCmdPara[]			= "spdCmdPara";
const char paraName_spdCmdStep[]			= "spdCmdStep";
const char paraName_speedAcc[]				= "speedAcc";
const char paraName_speedDec[]				= "speedDec";
const char paraName_curIqCmdPara[]			= "curIqCmdPara";
const char paraName_curIqCmdStep[]			= "curIqCmdStep";
const char paraName_iqthreshold[]           = "para_iqthreshold";
const char paraName_curIdCmdPara[]			= "curIdCmdPara";
const char paraName_curIdCmdStep[]			= "curIdCmdStep";
const char paraName_curIdCmdHold[]			= "curIdCmdHold";
const char paraName_startUpMethod[]			= "startUpMethod";
const char paraName_startUpStartAngle[]		= "startUpStartAngle";
const char paraName_startUpMoveTime[]		= "startUpMoveTime";
const char paraName_startUpCheckAngle[]		= "startUpCheckAngle";

const char paraName_led_mode[]				= "ledmode";
const char paraName_led_level[]				= "ledlevel";
const char paraName_led_levelmax[]			= "ledlevelmax";

const char paraName_tcurveVinit[]			= "tcurveVinit";
const char paraName_tcurveVend[]			= "tcurveVend";
const char paraName_tcurveVmax[]			= "tcurveVmax";
const char paraName_tcurveTacc[]			= "tcurveTacc";
const char paraName_tcurveTdec[]			= "tcurveTdec";

const char paraName_ctrlrMode[]	    		= "ctrlrMode";
const char paraName_homeMode[]				= "homeMode";
const char paraName_homeSpeed[]	   			= "homeSpeed";
const char paraName_homePos[]               = "homePos";
const char paraName_inPosRange[]			= "inPosRange";
const char paraName_zeroSpdRange[]			= "zeroSpdRange";
const char paraName_soft_neg_limit_enable[]	= "sofwareNeglimitEnable";
const char paraName_soft_neg_limit[]		= "sofwareNeglimit";
const char paraName_soft_pos_limit_enable[]	= "sofwarePoslimitEnable";
const char paraName_soft_pos_limit[]		= "sofwarePoslimit";
const char paraName_plsCmdType[]			= "plsCmdType";
const char paraName_plsCmdRev[]				= "plsCmdRev";
const char paraName_advCtrl0_enable[]		= "advCtrl0Enable";
const char paraName_advCtrl0_para0[]	    = "advCtrl0Para0";
const char paraName_advCtrl0_para1[]	    = "advCtrl0Para1";
const char paraName_advCtrl0_para2[]	    = "advCtrl0Para2";
const char paraName_advCtrl0_para3[]	    = "advCtrl0Para3";
const char paraName_advCtrl1_enable[]		= "advCtrl1Enable";
const char paraName_advCtrl1_para0[]	    = "advCtrl1Para0";
const char paraName_advCtrl1_para1[]	    = "advCtrl1Para1";
const char paraName_advCtrl1_para2[]	    = "advCtrl1Para2";
const char paraName_advCtrl1_para3[]	    = "advCtrl1Para3";
const char paraName_advCtrl2_enable[]		= "advCtrl2Enable";
const char paraName_advCtrl2_para0[]	    = "advCtrl2Para0";
const char paraName_advCtrl2_para1[]	    = "advCtrl2Para1";
const char paraName_advCtrl2_para2[]	    = "advCtrl2Para2";
const char paraName_advCtrl2_para3[]	    = "advCtrl2Para3";
const char paraName_advCtrl3_enable[]		= "advCtrl3Enable";
const char paraName_advCtrl3_para0[]	    = "advCtrl3Para0";
const char paraName_advCtrl3_para1[]	    = "advCtrl3Para1";
const char paraName_advCtrl3_para2[]	    = "advCtrl3Para2";
const char paraName_advCtrl3_para3[]	    = "advCtrl3Para3";
const char paraName_advCtrl4_enable[]		= "advCtrl4Enable";
const char paraName_advCtrl4_para0[]	    = "advCtrl4Para0";
const char paraName_advCtrl4_para1[]	    = "advCtrl4Para1";
const char paraName_advCtrl4_para2[]	    = "advCtrl4Para2";
const char paraName_advCtrl4_para3[]	    = "advCtrl4Para3";
const char paraName_advCtrl5_enable[]		= "advCtrl5Enable";
const char paraName_advCtrl5_para0[]	    = "advCtrl5Para0";
const char paraName_advCtrl5_para1[]	    = "advCtrl5Para1";
const char paraName_advCtrl5_para2[]	    = "advCtrl5Para2";
const char paraName_advCtrl5_para3[]	    = "advCtrl5Para3";
const char paraName_advCtrl6_enable[]    	= "advCtrl6Enable";
const char paraName_advCtrl6_para0[]	    = "advCtrl6Para0";
const char paraName_advCtrl6_para1[]	    = "advCtrl6Para1";
const char paraName_advCtrl6_para2[]	    = "advCtrl6Para2";
const char paraName_advCtrl6_para3[]	    = "advCtrl6Para3";
const char paraName_advCtrl7_enable[]    	= "advCtrl7Enable";
const char paraName_advCtrl7_para0[]	    = "advCtrl7Para0";
const char paraName_advCtrl7_para1[]	    = "advCtrl7Para1";
const char paraName_advCtrl7_para2[]	    = "advCtrl7Para2";
const char paraName_advCtrl7_para3[]	    = "advCtrl7Para3";
const char paraName_advCtrl8_enable[]    	= "advCtrl8Enable";
const char paraName_advCtrl8_para0[]	    = "advCtrl8Para0";
const char paraName_advCtrl8_para1[]	    = "advCtrl8Para1";
const char paraName_advCtrl8_para2[]	    = "advCtrl8Para2";
const char paraName_advCtrl8_para3[]	    = "advCtrl8Para3";
const char paraName_advCtrl9_enable[]    	= "advCtrl9Enable";
const char paraName_advCtrl9_para0[]	    = "advCtrl9Para0";
const char paraName_advCtrl9_para1[]	    = "advCtrl9Para1";
const char paraName_advCtrl9_para2[]	    = "advCtrl9Para2";
const char paraName_advCtrl9_para3[]	    = "advCtrl9Para3";
const char paraName_motorType[]				= "motorType";
const char paraName_encoderType[]			= "encoderType";
const char paraName_encoderDir[]			= "encoderDir";
const char paraName_encoderResolution[]		= "encoderResolution";
const char paraName_angleOffset[]			= "angleOffset";
const char paraName_dout0[]					= "dout0";
const char paraName_flashkey[]				= "para_flashkey";
const char paraName_paraMode[]				= "paraMode";
const char paraName_printInfo[]				= "printInfo";
const char paraName_printAll[]				= "printAll";
const char paraName_reset[]			   		= "reset";
const char paraName_saveAll[]				= "saveAll";

const PARAMETER paraDefault[MAX_PARAMETER] =
{
		PR_000_DEFAULT,
		PR_001_DEFAULT,
		PR_002_DEFAULT,
		PR_003_DEFAULT,
		PR_004_DEFAULT,
		PR_005_DEFAULT,
		PR_006_DEFAULT,
		PR_007_DEFAULT,
		PR_008_DEFAULT,
		PR_009_DEFAULT,
		PR_010_DEFAULT,
		PR_011_DEFAULT,
		PR_012_DEFAULT,
		PR_013_DEFAULT,
		PR_014_DEFAULT,
		PR_015_DEFAULT,
		PR_016_DEFAULT,
		PR_017_DEFAULT,
		PR_018_DEFAULT,
		PR_019_DEFAULT,
		PR_020_DEFAULT,
		PR_021_DEFAULT,
		PR_022_DEFAULT,
		PR_023_DEFAULT,
		PR_024_DEFAULT,
		PR_025_DEFAULT,
		PR_026_DEFAULT,
		PR_027_DEFAULT,
		PR_028_DEFAULT,
		PR_029_DEFAULT,
		PR_030_DEFAULT,
		PR_031_DEFAULT,
		PR_032_DEFAULT,
		PR_033_DEFAULT,
		PR_034_DEFAULT,
		PR_035_DEFAULT,
		PR_036_DEFAULT,
		PR_037_DEFAULT,
		PR_038_DEFAULT,
		PR_039_DEFAULT,
		PR_040_DEFAULT,
		PR_041_DEFAULT,
		PR_042_DEFAULT,
		PR_043_DEFAULT,
		PR_044_DEFAULT,
		PR_045_DEFAULT,
		PR_046_DEFAULT,
		PR_047_DEFAULT,
		PR_048_DEFAULT,
		PR_049_DEFAULT,
		PR_050_DEFAULT,
		PR_051_DEFAULT,
		PR_052_DEFAULT,
		PR_053_DEFAULT,
		PR_054_DEFAULT,
		PR_055_DEFAULT,
		PR_056_DEFAULT,
		PR_057_DEFAULT,
		PR_058_DEFAULT,
		PR_059_DEFAULT,
		PR_060_DEFAULT,
		PR_061_DEFAULT,
		PR_062_DEFAULT,
		PR_063_DEFAULT,
		PR_064_DEFAULT,
		PR_065_DEFAULT,
		PR_066_DEFAULT,
		PR_067_DEFAULT,
		PR_068_DEFAULT,
		PR_069_DEFAULT,
		PR_070_DEFAULT,
		PR_071_DEFAULT,
		PR_072_DEFAULT,
		PR_073_DEFAULT,
		PR_074_DEFAULT,
		PR_075_DEFAULT,
		PR_076_DEFAULT,
		PR_077_DEFAULT,
		PR_078_DEFAULT,
		PR_079_DEFAULT,
		PR_080_DEFAULT,
		PR_081_DEFAULT,
		PR_082_DEFAULT,
		PR_083_DEFAULT,
		PR_084_DEFAULT,
		PR_085_DEFAULT,
		PR_086_DEFAULT,
		PR_087_DEFAULT,
		PR_088_DEFAULT,
		PR_089_DEFAULT,
		PR_090_DEFAULT,
		PR_091_DEFAULT,
		PR_092_DEFAULT,
		PR_093_DEFAULT,
		PR_094_DEFAULT,
		PR_095_DEFAULT,
		PR_096_DEFAULT,
		PR_097_DEFAULT,
		PR_098_DEFAULT,
		PR_099_DEFAULT,
		PR_100_DEFAULT,
		PR_101_DEFAULT,
		PR_102_DEFAULT,
		PR_103_DEFAULT,
		PR_104_DEFAULT,
		PR_105_DEFAULT,
		PR_106_DEFAULT,
		PR_107_DEFAULT,
		PR_108_DEFAULT,
		PR_109_DEFAULT,
		PR_110_DEFAULT,
		PR_111_DEFAULT,
		PR_112_DEFAULT,
		PR_113_DEFAULT,
		PR_114_DEFAULT,
		PR_115_DEFAULT,
		PR_116_DEFAULT,
		PR_117_DEFAULT,
		PR_118_DEFAULT,
		PR_119_DEFAULT,
		PR_120_DEFAULT,
		PR_121_DEFAULT,
		PR_122_DEFAULT,
		PR_123_DEFAULT,
		PR_124_DEFAULT,
		PR_125_DEFAULT,
		PR_126_DEFAULT,
		PR_127_DEFAULT,
		PR_128_DEFAULT,
		PR_129_DEFAULT,
		PR_130_DEFAULT,
		PR_131_DEFAULT,
		PR_132_DEFAULT,
		PR_133_DEFAULT,
		PR_134_DEFAULT,
		PR_135_DEFAULT,
		PR_136_DEFAULT,
		PR_137_DEFAULT,
		PR_138_DEFAULT,
		PR_139_DEFAULT,
		PR_140_DEFAULT,
		PR_141_DEFAULT,
		PR_142_DEFAULT,
		PR_143_DEFAULT,
		PR_144_DEFAULT,
		PR_145_DEFAULT,
		PR_146_DEFAULT,
		PR_147_DEFAULT,
		PR_148_DEFAULT,
		PR_149_DEFAULT,
		PR_150_DEFAULT,
		PR_151_DEFAULT,
		PR_152_DEFAULT,
		PR_153_DEFAULT,
		PR_154_DEFAULT,
		PR_155_DEFAULT,
		PR_156_DEFAULT,
		PR_157_DEFAULT,
		PR_158_DEFAULT,
		PR_159_DEFAULT,
		PR_160_DEFAULT,
		PR_161_DEFAULT,
		PR_162_DEFAULT,
		PR_163_DEFAULT,
		PR_164_DEFAULT,
		PR_165_DEFAULT,
		PR_166_DEFAULT,
		PR_167_DEFAULT,
		PR_168_DEFAULT,
		PR_169_DEFAULT,
		PR_170_DEFAULT,
		PR_171_DEFAULT,
		PR_172_DEFAULT,
		PR_173_DEFAULT,
		PR_174_DEFAULT,
		PR_175_DEFAULT,
		PR_176_DEFAULT,
		PR_177_DEFAULT,
		PR_178_DEFAULT,
		PR_179_DEFAULT,
		PR_180_DEFAULT,
		PR_181_DEFAULT,
		PR_182_DEFAULT,
		PR_183_DEFAULT,
		PR_184_DEFAULT,
		PR_185_DEFAULT,
		PR_186_DEFAULT,
		PR_187_DEFAULT,
		PR_188_DEFAULT,
		PR_189_DEFAULT,
		PR_190_DEFAULT,
		PR_191_DEFAULT,
		PR_192_DEFAULT,
		PR_193_DEFAULT,
		PR_194_DEFAULT,
		PR_195_DEFAULT,
		PR_196_DEFAULT,
		PR_197_DEFAULT,
		PR_198_DEFAULT,
		PR_199_DEFAULT,
		PR_200_DEFAULT,
		PR_201_DEFAULT,
		PR_202_DEFAULT,
		PR_203_DEFAULT,
		PR_204_DEFAULT,
		PR_205_DEFAULT,
		PR_206_DEFAULT,
		PR_207_DEFAULT,
		PR_208_DEFAULT,
		PR_209_DEFAULT,
		PR_210_DEFAULT,
		PR_211_DEFAULT,
		PR_212_DEFAULT,
		PR_213_DEFAULT,
		PR_214_DEFAULT,
		PR_215_DEFAULT,
		PR_216_DEFAULT,
		PR_217_DEFAULT,
		PR_218_DEFAULT,
		PR_219_DEFAULT,
		PR_220_DEFAULT,
		PR_221_DEFAULT,
		PR_222_DEFAULT,
		PR_223_DEFAULT,
		PR_224_DEFAULT,
		PR_225_DEFAULT,
		PR_226_DEFAULT,
		PR_227_DEFAULT,
		PR_228_DEFAULT,
		PR_229_DEFAULT,
		PR_230_DEFAULT,
		PR_231_DEFAULT,
		PR_232_DEFAULT,
		PR_233_DEFAULT,
		PR_234_DEFAULT,
		PR_235_DEFAULT,
		PR_236_DEFAULT,
		PR_237_DEFAULT,
		PR_238_DEFAULT,
		PR_239_DEFAULT,
		PR_240_DEFAULT,
		PR_241_DEFAULT,
		PR_242_DEFAULT,
		PR_243_DEFAULT,
		PR_244_DEFAULT,
		PR_245_DEFAULT,
		PR_246_DEFAULT,
		PR_247_DEFAULT,
		PR_248_DEFAULT,
		PR_249_DEFAULT,
		PR_250_DEFAULT,
		PR_251_DEFAULT,
		PR_252_DEFAULT,
		PR_253_DEFAULT,
		PR_254_DEFAULT,
		PR_255_DEFAULT,
		PR_256_DEFAULT,
		PR_257_DEFAULT,
		PR_258_DEFAULT,
		PR_259_DEFAULT,
		PR_260_DEFAULT,
		PR_261_DEFAULT,
		PR_262_DEFAULT,
		PR_263_DEFAULT,
		PR_264_DEFAULT,
		PR_265_DEFAULT,
		PR_266_DEFAULT,
		PR_267_DEFAULT,
		PR_268_DEFAULT,
		PR_269_DEFAULT,
		PR_270_DEFAULT,
		PR_271_DEFAULT,
		PR_272_DEFAULT,
		PR_273_DEFAULT,
		PR_274_DEFAULT,
		PR_275_DEFAULT,
		PR_276_DEFAULT,
		PR_277_DEFAULT,
		PR_278_DEFAULT,
		PR_279_DEFAULT,
		PR_280_DEFAULT,
		PR_281_DEFAULT,
		PR_282_DEFAULT,
		PR_283_DEFAULT,
		PR_284_DEFAULT,
		PR_285_DEFAULT,
		PR_286_DEFAULT,
		PR_287_DEFAULT,
		PR_288_DEFAULT,
		PR_289_DEFAULT,
		PR_290_DEFAULT,
		PR_291_DEFAULT,
		PR_292_DEFAULT,
		PR_293_DEFAULT,
		PR_294_DEFAULT,
		PR_295_DEFAULT,
		PR_296_DEFAULT,
		PR_297_DEFAULT,
		PR_298_DEFAULT,
		PR_299_DEFAULT,
		PR_300_DEFAULT,
		PR_301_DEFAULT,
		PR_302_DEFAULT,
		PR_303_DEFAULT,
		PR_304_DEFAULT,
		PR_305_DEFAULT,
		PR_306_DEFAULT,
		PR_307_DEFAULT,
		PR_308_DEFAULT,
		PR_309_DEFAULT,
		PR_310_DEFAULT,
		PR_311_DEFAULT,
		PR_312_DEFAULT,
		PR_313_DEFAULT,
		PR_314_DEFAULT,
		PR_315_DEFAULT,
		PR_316_DEFAULT,
		PR_317_DEFAULT,
		PR_318_DEFAULT,
		PR_319_DEFAULT,
		PR_320_DEFAULT,
		PR_321_DEFAULT,
		PR_322_DEFAULT,
		PR_323_DEFAULT,
		PR_324_DEFAULT,
		PR_325_DEFAULT,
		PR_326_DEFAULT,
		PR_327_DEFAULT,
		PR_328_DEFAULT,
		PR_329_DEFAULT,
		PR_330_DEFAULT,
		PR_331_DEFAULT,
		PR_332_DEFAULT,
		PR_333_DEFAULT,
		PR_334_DEFAULT,
		PR_335_DEFAULT,
		PR_336_DEFAULT,
		PR_337_DEFAULT,
		PR_338_DEFAULT,
		PR_339_DEFAULT,
		PR_340_DEFAULT,
		PR_341_DEFAULT,
		PR_342_DEFAULT,
		PR_343_DEFAULT,
		PR_344_DEFAULT,
		PR_345_DEFAULT,
		PR_346_DEFAULT,
		PR_347_DEFAULT,
		PR_348_DEFAULT,
		PR_349_DEFAULT,
		PR_350_DEFAULT,
		PR_351_DEFAULT,
		PR_352_DEFAULT,
		PR_353_DEFAULT,
		PR_354_DEFAULT,
		PR_355_DEFAULT,
		PR_356_DEFAULT,
		PR_357_DEFAULT,
		PR_358_DEFAULT,
		PR_359_DEFAULT,
		PR_360_DEFAULT,
		PR_361_DEFAULT,
		PR_362_DEFAULT,
		PR_363_DEFAULT,
		PR_364_DEFAULT,
		PR_365_DEFAULT,
		PR_366_DEFAULT,
		PR_367_DEFAULT,
		PR_368_DEFAULT,
		PR_369_DEFAULT,
		PR_370_DEFAULT,
		PR_371_DEFAULT,
		PR_372_DEFAULT,
		PR_373_DEFAULT,
		PR_374_DEFAULT,
		PR_375_DEFAULT,
		PR_376_DEFAULT,
		PR_377_DEFAULT,
		PR_378_DEFAULT,
		PR_379_DEFAULT,
		PR_380_DEFAULT,
		PR_381_DEFAULT,
		PR_382_DEFAULT,
		PR_383_DEFAULT,
		PR_384_DEFAULT,
		PR_385_DEFAULT,
		PR_386_DEFAULT,
		PR_387_DEFAULT,
		PR_388_DEFAULT,
		PR_389_DEFAULT,
		PR_390_DEFAULT,
		PR_391_DEFAULT,
		PR_392_DEFAULT,
		PR_393_DEFAULT,
		PR_394_DEFAULT,
		PR_395_DEFAULT,
		PR_396_DEFAULT,
		PR_397_DEFAULT,
		PR_398_DEFAULT,
		PR_399_DEFAULT,
		PR_400_DEFAULT,
		PR_401_DEFAULT,
		PR_402_DEFAULT,
		PR_403_DEFAULT,
		PR_404_DEFAULT,
		PR_405_DEFAULT,
		PR_406_DEFAULT,
		PR_407_DEFAULT,
		PR_408_DEFAULT,
		PR_409_DEFAULT,
		PR_410_DEFAULT,
		PR_411_DEFAULT,
		PR_412_DEFAULT,
		PR_413_DEFAULT,
		PR_414_DEFAULT,
		PR_415_DEFAULT,
		PR_416_DEFAULT,
		PR_417_DEFAULT,
		PR_418_DEFAULT,
		PR_419_DEFAULT,
		PR_420_DEFAULT,
		PR_421_DEFAULT,
		PR_422_DEFAULT,
		PR_423_DEFAULT,
		PR_424_DEFAULT,
		PR_425_DEFAULT,
		PR_426_DEFAULT,
		PR_427_DEFAULT,
		PR_428_DEFAULT,
		PR_429_DEFAULT,
		PR_430_DEFAULT,
		PR_431_DEFAULT,
		PR_432_DEFAULT,
		PR_433_DEFAULT,
		PR_434_DEFAULT,
		PR_435_DEFAULT,
		PR_436_DEFAULT,
		PR_437_DEFAULT,
		PR_438_DEFAULT,
		PR_439_DEFAULT,
		PR_440_DEFAULT,
		PR_441_DEFAULT,
		PR_442_DEFAULT,
		PR_443_DEFAULT,
		PR_444_DEFAULT,
		PR_445_DEFAULT,
		PR_446_DEFAULT,
		PR_447_DEFAULT,
		PR_448_DEFAULT,
		PR_449_DEFAULT,
		PR_450_DEFAULT,
		PR_451_DEFAULT,
		PR_452_DEFAULT,
		PR_453_DEFAULT,
		PR_454_DEFAULT,
		PR_455_DEFAULT,
		PR_456_DEFAULT,
		PR_457_DEFAULT,
		PR_458_DEFAULT,
		PR_459_DEFAULT,
		PR_460_DEFAULT,
		PR_461_DEFAULT,
		PR_462_DEFAULT,
		PR_463_DEFAULT,
		PR_464_DEFAULT,
		PR_465_DEFAULT,
		PR_466_DEFAULT,
		PR_467_DEFAULT,
		PR_468_DEFAULT,
		PR_469_DEFAULT,
		PR_470_DEFAULT,
		PR_471_DEFAULT,
		PR_472_DEFAULT,
		PR_473_DEFAULT,
		PR_474_DEFAULT,
		PR_475_DEFAULT,
		PR_476_DEFAULT,
		PR_477_DEFAULT,
		PR_478_DEFAULT,
		PR_479_DEFAULT,
		PR_480_DEFAULT,
		PR_481_DEFAULT,
		PR_482_DEFAULT,
		PR_483_DEFAULT,
		PR_484_DEFAULT,
		PR_485_DEFAULT,
		PR_486_DEFAULT,
		PR_487_DEFAULT,
		PR_488_DEFAULT,
		PR_489_DEFAULT,
		PR_490_DEFAULT,
		PR_491_DEFAULT,
		PR_492_DEFAULT,
		PR_493_DEFAULT,
		PR_494_DEFAULT,
		PR_495_DEFAULT,
		PR_496_DEFAULT,
		PR_497_DEFAULT,
		PR_498_DEFAULT,
		PR_499_DEFAULT,
		PR_500_DEFAULT,
		PR_501_DEFAULT,
		PR_502_DEFAULT,
		PR_503_DEFAULT,
		PR_504_DEFAULT,
		PR_505_DEFAULT,
		PR_506_DEFAULT,
		PR_507_DEFAULT,
		PR_508_DEFAULT,
		PR_509_DEFAULT,
		PR_510_DEFAULT,
		PR_511_DEFAULT,
};
