////*****************************************////
//  Name : drv_device_enc.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "drv_device.h"

enc_config_t stEncoder_config_pulseCommand_abMode =
{
  .decoderWorkMode = kENC_DecoderWorkAsNormalMode,
  .enableReverseDirection = false,
  .HOMETriggerMode = kENC_HOMETriggerDisabled,
  .INDEXTriggerMode = kENC_INDEXTriggerDisabled,
  .positionInitialValue = 0,
  .enableTRIGGERClearPositionCounter = false,
  .enableTRIGGERClearHoldPositionCounter = true,
  .positionMatchMode = kENC_POSMATCHOnPositionCounterEqualToComapreValue,
  .positionCompareValue = 4294967295,
  .revolutionCountCondition = kENC_RevolutionCountOnINDEXPulse,
  .enableModuloCountMode = false,
  .positionModulusValue = 0,
  .enableWatchdog = false,
  .watchdogTimeoutValue = 0,
  .filterCount = 0,
  .filterSamplePeriod = 0
};

enc_config_t stEncoder_config_pulseCommand_pulseDirMode =
{
  .decoderWorkMode = kENC_DecoderWorkAsSignalPhaseCountMode,
  .enableReverseDirection = false,
  .HOMETriggerMode = kENC_HOMETriggerDisabled,
  .INDEXTriggerMode = kENC_INDEXTriggerDisabled,
  .positionInitialValue = 0,
  .enableTRIGGERClearPositionCounter = false,
  .enableTRIGGERClearHoldPositionCounter = true,
  .positionMatchMode = kENC_POSMATCHOnPositionCounterEqualToComapreValue,
  .positionCompareValue = 4294967295,
  .revolutionCountCondition = kENC_RevolutionCountOnINDEXPulse,
  .enableModuloCountMode = false,
  .positionModulusValue = 0,
  .enableWatchdog = false,
  .watchdogTimeoutValue = 0,
  .filterCount = 0,
  .filterSamplePeriod = 0
};

enc_config_t stEncoder_config_encoder_zeroAngleCloseMode = {
  .decoderWorkMode = kENC_DecoderWorkAsNormalMode,
  .enableReverseDirection = false,
  .HOMETriggerMode = kENC_HOMETriggerDisabled,
  .INDEXTriggerMode = kENC_INDEXTriggerDisabled,
  .positionInitialValue = 0,
  .enableTRIGGERClearPositionCounter = false,
  .enableTRIGGERClearHoldPositionCounter = true,
  .positionMatchMode = kENC_POSMATCHOnPositionCounterEqualToComapreValue,
  .positionCompareValue = 4294967295,
  .revolutionCountCondition = kENC_RevolutionCountOnINDEXPulse,
  .enableModuloCountMode = false,
  .positionModulusValue = 0,
  .enableWatchdog = false,
  .watchdogTimeoutValue = 0,
  .filterCount = 0,
  .filterSamplePeriod = 1
};

void device_encoder_reverse(ENC_Type *base)
{
	 base->CTRL |= ENC_CTRL_REV_MASK;
}
