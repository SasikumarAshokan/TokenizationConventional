//
//
// Copyright © 2023 THALES. All rights reserved.
//
    

#ifndef D1CCardEnumsCaaS_h
#define D1CCardEnumsCaaS_h

typedef NS_ENUM(NSInteger, D1COngoingOperation)
{
    D1COngoingOperationNone,
    D1COngoingOperationRenewal
};

typedef NS_ENUM(NSInteger, D1CStateReason)
{
    D1CStateReasonNone,
    D1CStateReasonClosedAccount,
    D1CStateReasonClosedCard,
    D1CStateReasonCardLost,
    D1CStateReasonCardFound,
    D1CStateReasonCardStolen,
    D1CStateReasonCardBroken,
    D1CStateReasonCardNotReceived,
    D1CStateReasonFraud,
    D1CStateReasonUserDecision,
    D1CStateReasonBankDecision,
    D1CStateReasonIssuerDecision,
    D1CStateReasonPinLocked,
    D1CStateReasonCvv2Locked,
    D1CStateReasonExpiryDateLocked,
    D1CStateReasonTechnicalError,
    D1CStateReasonUpgrade
};

#endif /* D1CCardEnumsCaaS_h */
