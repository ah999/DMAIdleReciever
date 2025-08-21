/**
  ******************************************************************************
  * @file    stm32f4xx_hal_DMAIdleReciever.h
  * @author  MCD Application Team
  * @brief   Header file of DMAIdleReciever HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_HAL_DMAIdleReciever_H
#define __STM32F4xx_HAL_DMAIdleReciever_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup DMAIdleReciever
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup DMAIdleReciever_Exported_Types DMAIdleReciever Exported Types
  * @{
  */

/**
  * @brief DMAIdleReciever Init Structure definition
  */
typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the DMAIdleReciever communication baud rate.
                                           The baud rate is computed using the following formula:
                                           - IntegerDivider = ((PCLKx) / (8 * (OVR8+1) * (hDMAIdleReciever->Init.BaudRate)))
                                           - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 8 * (OVR8+1)) + 0.5
                                           Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */

  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref DMAIdleReciever_Word_Length */

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref DMAIdleReciever_Stop_Bits */

  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref DMAIdleReciever_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */

  uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref DMAIdleReciever_Mode */

  uint32_t HwFlowCtl;                 /*!< Specifies whether the hardware flow control mode is enabled or disabled.
                                           This parameter can be a value of @ref DMAIdleReciever_Hardware_Flow_Control */

  uint32_t OverSampling;              /*!< Specifies whether the Over sampling 8 is enabled or disabled, to achieve higher speed (up to fPCLK/8).
                                           This parameter can be a value of @ref DMAIdleReciever_Over_Sampling */
} DMAIdleReciever_InitTypeDef;

/**
  * @brief HAL DMAIdleReciever State structures definition
  * @note  HAL DMAIdleReciever State value is a combination of 2 different substates: gState and RxState.
  *        - gState contains DMAIdleReciever state information related to global Handle management
  *          and also information related to Tx operations.
  *          gState value coding follow below described bitmap :
  *          b7-b6  Error information
  *             00 : No Error
  *             01 : (Not Used)
  *             10 : Timeout
  *             11 : Error
  *          b5     Peripheral initialization status
  *             0  : Reset (Peripheral not initialized)
  *             1  : Init done (Peripheral initialized. HAL DMAIdleReciever Init function already called)
  *          b4-b3  (not used)
  *             xx : Should be set to 00
  *          b2     Intrinsic process state
  *             0  : Ready
  *             1  : Busy (Peripheral busy with some configuration or internal operations)
  *          b1     (not used)
  *             x  : Should be set to 0
  *          b0     Tx state
  *             0  : Ready (no Tx operation ongoing)
  *             1  : Busy (Tx operation ongoing)
  *        - RxState contains information related to Rx operations.
  *          RxState value coding follow below described bitmap :
  *          b7-b6  (not used)
  *             xx : Should be set to 00
  *          b5     Peripheral initialization status
  *             0  : Reset (Peripheral not initialized)
  *             1  : Init done (Peripheral initialized)
  *          b4-b2  (not used)
  *            xxx : Should be set to 000
  *          b1     Rx state
  *             0  : Ready (no Rx operation ongoing)
  *             1  : Busy (Rx operation ongoing)
  *          b0     (not used)
  *             x  : Should be set to 0.
  */
typedef enum
{
  HAL_DMAIdleReciever_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized
                                                   Value is allowed for gState and RxState */
  HAL_DMAIdleReciever_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use
                                                   Value is allowed for gState and RxState */
  HAL_DMAIdleReciever_STATE_BUSY              = 0x24U,    /*!< an internal process is ongoing
                                                   Value is allowed for gState only */
  HAL_DMAIdleReciever_STATE_BUSY_TX           = 0x21U,    /*!< Data Transmission process is ongoing
                                                   Value is allowed for gState only */
  HAL_DMAIdleReciever_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing
                                                   Value is allowed for RxState only */
  HAL_DMAIdleReciever_STATE_BUSY_TX_RX        = 0x23U,    /*!< Data Transmission and Reception process is ongoing
                                                   Not to be used for neither gState nor RxState.
                                                   Value is result of combination (Or) between gState and RxState values */
  HAL_DMAIdleReciever_STATE_TIMEOUT           = 0xA0U,    /*!< Timeout state
                                                   Value is allowed for gState only */
  HAL_DMAIdleReciever_STATE_ERROR             = 0xE0U     /*!< Error
                                                   Value is allowed for gState only */
} HAL_DMAIdleReciever_StateTypeDef;

/**
  * @brief HAL DMAIdleReciever Reception type definition
  * @note  HAL DMAIdleReciever Reception type value aims to identify which type of Reception is ongoing.
  *        This parameter can be a value of @ref DMAIdleReciever_Reception_Type_Values :
  *           HAL_DMAIdleReciever_RECEPTION_STANDARD         = 0x00U,
  *           HAL_DMAIdleReciever_RECEPTION_TOIDLE           = 0x01U,
  */
typedef uint32_t HAL_DMAIdleReciever_RxTypeTypeDef;

/**
  * @brief HAL DMAIdleReciever Rx Event type definition
  * @note  HAL DMAIdleReciever Rx Event type value aims to identify which type of Event has occurred
  *        leading to call of the RxEvent callback.
  *        This parameter can be a value of @ref DMAIdleReciever_RxEvent_Type_Values :
  *           HAL_DMAIdleReciever_RXEVENT_TC                 = 0x00U,
  *           HAL_DMAIdleReciever_RXEVENT_HT                 = 0x01U,
  *           HAL_DMAIdleReciever_RXEVENT_IDLE               = 0x02U,
  */
typedef uint32_t HAL_DMAIdleReciever_RxEventTypeTypeDef;

/**
  * @brief  DMAIdleReciever handle Structure definition
  */
typedef struct __DMAIdleReciever_HandleTypeDef
{
  USART_TypeDef                 *Instance;        /*!< DMAIdleReciever registers base address        */

  DMAIdleReciever_InitTypeDef              Init;             /*!< DMAIdleReciever communication parameters      */

  const uint8_t                 *pTxBuffPtr;      /*!< Pointer to DMAIdleReciever Tx transfer Buffer */

  uint16_t                      TxXferSize;       /*!< DMAIdleReciever Tx Transfer size              */

  __IO uint16_t                 TxXferCount;      /*!< DMAIdleReciever Tx Transfer Counter           */

  uint8_t                       *pRxBuffPtr;      /*!< Pointer to DMAIdleReciever Rx transfer Buffer */

  uint16_t                      RxXferSize;       /*!< DMAIdleReciever Rx Transfer size              */

  __IO uint16_t                 RxXferCount;      /*!< DMAIdleReciever Rx Transfer Counter           */

  __IO HAL_DMAIdleReciever_RxTypeTypeDef ReceptionType;      /*!< Type of ongoing reception          */

  __IO HAL_DMAIdleReciever_RxEventTypeTypeDef RxEventType;   /*!< Type of Rx Event                   */

  DMA_HandleTypeDef             *hdmatx;          /*!< DMAIdleReciever Tx DMA Handle parameters      */

  DMA_HandleTypeDef             *hdmarx;          /*!< DMAIdleReciever Rx DMA Handle parameters      */

  HAL_LockTypeDef               Lock;             /*!< Locking object                     */

  __IO HAL_DMAIdleReciever_StateTypeDef    gState;           /*!< DMAIdleReciever state information related to global Handle management
                                                       and also related to Tx operations.
                                                       This parameter can be a value of @ref HAL_DMAIdleReciever_StateTypeDef */

  __IO HAL_DMAIdleReciever_StateTypeDef    RxState;          /*!< DMAIdleReciever state information related to Rx operations.
                                                       This parameter can be a value of @ref HAL_DMAIdleReciever_StateTypeDef */

  __IO uint32_t                 ErrorCode;        /*!< DMAIdleReciever Error code                    */

#if (USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS == 1)
  void (* TxHalfCpltCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);        /*!< DMAIdleReciever Tx Half Complete Callback        */
  void (* TxCpltCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);            /*!< DMAIdleReciever Tx Complete Callback             */
  void (* RxHalfCpltCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);        /*!< DMAIdleReciever Rx Half Complete Callback        */
  void (* RxCpltCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);            /*!< DMAIdleReciever Rx Complete Callback             */
  void (* ErrorCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);             /*!< DMAIdleReciever Error Callback                   */
  void (* AbortCpltCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);         /*!< DMAIdleReciever Abort Complete Callback          */
  void (* AbortTransmitCpltCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever); /*!< DMAIdleReciever Abort Transmit Complete Callback */
  void (* AbortReceiveCpltCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);  /*!< DMAIdleReciever Abort Receive Complete Callback  */
  void (* WakeupCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);            /*!< DMAIdleReciever Wakeup Callback                  */
  void (* RxEventCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint16_t Pos); /*!< DMAIdleReciever Reception Event Callback     */

  void (* MspInitCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);           /*!< DMAIdleReciever Msp Init callback                */
  void (* MspDeInitCallback)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);         /*!< DMAIdleReciever Msp DeInit callback              */
#endif  /* USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS */

} DMAIdleReciever_HandleTypeDef;

#if (USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL DMAIdleReciever Callback ID enumeration definition
  */
typedef enum
{
  HAL_DMAIdleReciever_TX_HALFCOMPLETE_CB_ID         = 0x00U,    /*!< DMAIdleReciever Tx Half Complete Callback ID        */
  HAL_DMAIdleReciever_TX_COMPLETE_CB_ID             = 0x01U,    /*!< DMAIdleReciever Tx Complete Callback ID             */
  HAL_DMAIdleReciever_RX_HALFCOMPLETE_CB_ID         = 0x02U,    /*!< DMAIdleReciever Rx Half Complete Callback ID        */
  HAL_DMAIdleReciever_RX_COMPLETE_CB_ID             = 0x03U,    /*!< DMAIdleReciever Rx Complete Callback ID             */
  HAL_DMAIdleReciever_ERROR_CB_ID                   = 0x04U,    /*!< DMAIdleReciever Error Callback ID                   */
  HAL_DMAIdleReciever_ABORT_COMPLETE_CB_ID          = 0x05U,    /*!< DMAIdleReciever Abort Complete Callback ID          */
  HAL_DMAIdleReciever_ABORT_TRANSMIT_COMPLETE_CB_ID = 0x06U,    /*!< DMAIdleReciever Abort Transmit Complete Callback ID */
  HAL_DMAIdleReciever_ABORT_RECEIVE_COMPLETE_CB_ID  = 0x07U,    /*!< DMAIdleReciever Abort Receive Complete Callback ID  */
  HAL_DMAIdleReciever_WAKEUP_CB_ID                  = 0x08U,    /*!< DMAIdleReciever Wakeup Callback ID                  */

  HAL_DMAIdleReciever_MSPINIT_CB_ID                 = 0x0BU,    /*!< DMAIdleReciever MspInit callback ID                 */
  HAL_DMAIdleReciever_MSPDEINIT_CB_ID               = 0x0CU     /*!< DMAIdleReciever MspDeInit callback ID               */

} HAL_DMAIdleReciever_CallbackIDTypeDef;

/**
  * @brief  HAL DMAIdleReciever Callback pointer definition
  */
typedef  void (*pDMAIdleReciever_CallbackTypeDef)(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);  /*!< pointer to an DMAIdleReciever callback function */
typedef  void (*pDMAIdleReciever_RxEventCallbackTypeDef)(struct __DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint16_t Pos);   /*!< pointer to a DMAIdleReciever Rx Event specific callback function */

#endif /* USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DMAIdleReciever_Exported_Constants DMAIdleReciever Exported Constants
  * @{
  */

/** @defgroup DMAIdleReciever_Error_Code DMAIdleReciever Error Code
  * @{
  */
#define HAL_DMAIdleReciever_ERROR_NONE              0x00000000U   /*!< No error            */
#define HAL_DMAIdleReciever_ERROR_PE                0x00000001U   /*!< Parity error        */
#define HAL_DMAIdleReciever_ERROR_NE                0x00000002U   /*!< Noise error         */
#define HAL_DMAIdleReciever_ERROR_FE                0x00000004U   /*!< Frame error         */
#define HAL_DMAIdleReciever_ERROR_ORE               0x00000008U   /*!< Overrun error       */
#define HAL_DMAIdleReciever_ERROR_DMA               0x00000010U   /*!< DMA transfer error  */
#if (USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS == 1)
#define  HAL_DMAIdleReciever_ERROR_INVALID_CALLBACK 0x00000020U   /*!< Invalid Callback error  */
#endif /* USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup DMAIdleReciever_Word_Length DMAIdleReciever Word Length
  * @{
  */
#define DMAIdleReciever_WORDLENGTH_8B                  0x00000000U
#define DMAIdleReciever_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M)
/**
  * @}
  */

/** @defgroup DMAIdleReciever_Stop_Bits DMAIdleReciever Number of Stop Bits
  * @{
  */
#define DMAIdleReciever_STOPBITS_1                     0x00000000U
#define DMAIdleReciever_STOPBITS_2                     ((uint32_t)USART_CR2_STOP_1)
/**
  * @}
  */

/** @defgroup DMAIdleReciever_Parity DMAIdleReciever Parity
  * @{
  */
#define DMAIdleReciever_PARITY_NONE                    0x00000000U
#define DMAIdleReciever_PARITY_EVEN                    ((uint32_t)USART_CR1_PCE)
#define DMAIdleReciever_PARITY_ODD                     ((uint32_t)(USART_CR1_PCE | USART_CR1_PS))
/**
  * @}
  */

/** @defgroup DMAIdleReciever_Hardware_Flow_Control DMAIdleReciever Hardware Flow Control
  * @{
  */
#define DMAIdleReciever_HWCONTROL_NONE                  0x00000000U
#define DMAIdleReciever_HWCONTROL_RTS                   ((uint32_t)USART_CR3_RTSE)
#define DMAIdleReciever_HWCONTROL_CTS                   ((uint32_t)USART_CR3_CTSE)
#define DMAIdleReciever_HWCONTROL_RTS_CTS               ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))
/**
  * @}
  */

/** @defgroup DMAIdleReciever_Mode DMAIdleReciever Transfer Mode
  * @{
  */
#define DMAIdleReciever_MODE_RX                        ((uint32_t)USART_CR1_RE)
#define DMAIdleReciever_MODE_TX                        ((uint32_t)USART_CR1_TE)
#define DMAIdleReciever_MODE_TX_RX                     ((uint32_t)(USART_CR1_TE | USART_CR1_RE))
/**
  * @}
  */

/** @defgroup DMAIdleReciever_State DMAIdleReciever State
  * @{
  */
#define DMAIdleReciever_STATE_DISABLE                  0x00000000U
#define DMAIdleReciever_STATE_ENABLE                   ((uint32_t)USART_CR1_UE)
/**
  * @}
  */

/** @defgroup DMAIdleReciever_Over_Sampling DMAIdleReciever Over Sampling
  * @{
  */
#define DMAIdleReciever_OVERSAMPLING_16                    0x00000000U
#define DMAIdleReciever_OVERSAMPLING_8                     ((uint32_t)USART_CR1_OVER8)
/**
  * @}
  */

/** @defgroup DMAIdleReciever_LIN_Break_Detection_Length  DMAIdleReciever LIN Break Detection Length
  * @{
  */
#define DMAIdleReciever_LINBREAKDETECTLENGTH_10B      0x00000000U
#define DMAIdleReciever_LINBREAKDETECTLENGTH_11B      ((uint32_t)USART_CR2_LBDL)
/**
  * @}
  */

/** @defgroup DMAIdleReciever_WakeUp_functions  DMAIdleReciever Wakeup Functions
  * @{
  */
#define DMAIdleReciever_WAKEUPMETHOD_IDLELINE                0x00000000U
#define DMAIdleReciever_WAKEUPMETHOD_ADDRESSMARK             ((uint32_t)USART_CR1_WAKE)
/**
  * @}
  */

/** @defgroup DMAIdleReciever_Flags   DMAIdleReciever FLags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the SR register
  * @{
  */
#define DMAIdleReciever_FLAG_CTS                       ((uint32_t)USART_SR_CTS)
#define DMAIdleReciever_FLAG_LBD                       ((uint32_t)USART_SR_LBD)
#define DMAIdleReciever_FLAG_TXE                       ((uint32_t)USART_SR_TXE)
#define DMAIdleReciever_FLAG_TC                        ((uint32_t)USART_SR_TC)
#define DMAIdleReciever_FLAG_RXNE                      ((uint32_t)USART_SR_RXNE)
#define DMAIdleReciever_FLAG_IDLE                      ((uint32_t)USART_SR_IDLE)
#define DMAIdleReciever_FLAG_ORE                       ((uint32_t)USART_SR_ORE)
#define DMAIdleReciever_FLAG_NE                        ((uint32_t)USART_SR_NE)
#define DMAIdleReciever_FLAG_FE                        ((uint32_t)USART_SR_FE)
#define DMAIdleReciever_FLAG_PE                        ((uint32_t)USART_SR_PE)
/**
  * @}
  */

/** @defgroup DMAIdleReciever_Interrupt_definition  DMAIdleReciever Interrupt Definitions
  *        Elements values convention: 0xY000XXXX
  *           - XXXX  : Interrupt mask (16 bits) in the Y register
  *           - Y  : Interrupt source register (2bits)
  *                   - 0001: CR1 register
  *                   - 0010: CR2 register
  *                   - 0011: CR3 register
  * @{
  */

#define DMAIdleReciever_IT_PE                       ((uint32_t)(DMAIdleReciever_CR1_REG_INDEX << 28U | USART_CR1_PEIE))
#define DMAIdleReciever_IT_TXE                      ((uint32_t)(DMAIdleReciever_CR1_REG_INDEX << 28U | USART_CR1_TXEIE))
#define DMAIdleReciever_IT_TC                       ((uint32_t)(DMAIdleReciever_CR1_REG_INDEX << 28U | USART_CR1_TCIE))
#define DMAIdleReciever_IT_RXNE                     ((uint32_t)(DMAIdleReciever_CR1_REG_INDEX << 28U | USART_CR1_RXNEIE))
#define DMAIdleReciever_IT_IDLE                     ((uint32_t)(DMAIdleReciever_CR1_REG_INDEX << 28U | USART_CR1_IDLEIE))

#define DMAIdleReciever_IT_LBD                      ((uint32_t)(DMAIdleReciever_CR2_REG_INDEX << 28U | USART_CR2_LBDIE))

#define DMAIdleReciever_IT_CTS                      ((uint32_t)(DMAIdleReciever_CR3_REG_INDEX << 28U | USART_CR3_CTSIE))
#define DMAIdleReciever_IT_ERR                      ((uint32_t)(DMAIdleReciever_CR3_REG_INDEX << 28U | USART_CR3_EIE))
/**
  * @}
  */

/** @defgroup DMAIdleReciever_Reception_Type_Values  DMAIdleReciever Reception type values
  * @{
  */
#define HAL_DMAIdleReciever_RECEPTION_STANDARD          (0x00000000U)             /*!< Standard reception                       */
#define HAL_DMAIdleReciever_RECEPTION_TOIDLE            (0x00000001U)             /*!< Reception till completion or IDLE event  */
/**
  * @}
  */

/** @defgroup DMAIdleReciever_RxEvent_Type_Values  DMAIdleReciever RxEvent type values
  * @{
  */
#define HAL_DMAIdleReciever_RXEVENT_TC                  (0x00000000U)             /*!< RxEvent linked to Transfer Complete event */
#define HAL_DMAIdleReciever_RXEVENT_HT                  (0x00000001U)             /*!< RxEvent linked to Half Transfer event     */
#define HAL_DMAIdleReciever_RXEVENT_IDLE                (0x00000002U)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DMAIdleReciever_Exported_Macros DMAIdleReciever Exported Macros
  * @{
  */

/** @brief Reset DMAIdleReciever handle gstate & RxState
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @retval None
  */
#if (USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS == 1)
#define __HAL_DMAIdleReciever_RESET_HANDLE_STATE(__HANDLE__)  do{                                                   \
                                                       (__HANDLE__)->gState = HAL_DMAIdleReciever_STATE_RESET;      \
                                                       (__HANDLE__)->RxState = HAL_DMAIdleReciever_STATE_RESET;     \
                                                       (__HANDLE__)->MspInitCallback = NULL;             \
                                                       (__HANDLE__)->MspDeInitCallback = NULL;           \
                                                     } while(0U)
#else
#define __HAL_DMAIdleReciever_RESET_HANDLE_STATE(__HANDLE__)  do{                                                   \
                                                       (__HANDLE__)->gState = HAL_DMAIdleReciever_STATE_RESET;      \
                                                       (__HANDLE__)->RxState = HAL_DMAIdleReciever_STATE_RESET;     \
                                                     } while(0U)
#endif /*USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS */

/** @brief  Flushes the DMAIdleReciever DR register
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  */
#define __HAL_DMAIdleReciever_FLUSH_DRREGISTER(__HANDLE__) ((__HANDLE__)->Instance->DR)

/** @brief  Checks whether the specified DMAIdleReciever flag is set or not.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @param  __FLAG__ specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg DMAIdleReciever_FLAG_CTS:  CTS Change flag (not available for DMAIdleReciever4 and DMAIdleReciever5)
  *            @arg DMAIdleReciever_FLAG_LBD:  LIN Break detection flag
  *            @arg DMAIdleReciever_FLAG_TXE:  Transmit data register empty flag
  *            @arg DMAIdleReciever_FLAG_TC:   Transmission Complete flag
  *            @arg DMAIdleReciever_FLAG_RXNE: Receive data register not empty flag
  *            @arg DMAIdleReciever_FLAG_IDLE: Idle Line detection flag
  *            @arg DMAIdleReciever_FLAG_ORE:  Overrun Error flag
  *            @arg DMAIdleReciever_FLAG_NE:   Noise Error flag
  *            @arg DMAIdleReciever_FLAG_FE:   Framing Error flag
  *            @arg DMAIdleReciever_FLAG_PE:   Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_DMAIdleReciever_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->SR & (__FLAG__)) == (__FLAG__))

/** @brief  Clears the specified DMAIdleReciever pending flag.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg DMAIdleReciever_FLAG_CTS:  CTS Change flag (not available for DMAIdleReciever4 and DMAIdleReciever5).
  *            @arg DMAIdleReciever_FLAG_LBD:  LIN Break detection flag.
  *            @arg DMAIdleReciever_FLAG_TC:   Transmission Complete flag.
  *            @arg DMAIdleReciever_FLAG_RXNE: Receive data register not empty flag.
  *
  * @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (Overrun
  *          error) and IDLE (Idle line detected) flags are cleared by software
  *          sequence: a read operation to USART_SR register followed by a read
  *          operation to USART_DR register.
  * @note   RXNE flag can be also cleared by a read to the USART_DR register.
  * @note   TC flag can be also cleared by software sequence: a read operation to
  *          USART_SR register followed by a write operation to USART_DR register.
  * @note   TXE flag is cleared only by a write to the USART_DR register.
  *
  * @retval None
  */
#define __HAL_DMAIdleReciever_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->SR = ~(__FLAG__))

/** @brief  Clears the DMAIdleReciever PE pending flag.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @retval None
  */
#define __HAL_DMAIdleReciever_CLEAR_PEFLAG(__HANDLE__)     \
  do{                                           \
    __IO uint32_t tmpreg = 0x00U;               \
    tmpreg = (__HANDLE__)->Instance->SR;        \
    tmpreg = (__HANDLE__)->Instance->DR;        \
    UNUSED(tmpreg);                             \
  } while(0U)

/** @brief  Clears the DMAIdleReciever FE pending flag.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @retval None
  */
#define __HAL_DMAIdleReciever_CLEAR_FEFLAG(__HANDLE__) __HAL_DMAIdleReciever_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Clears the DMAIdleReciever NE pending flag.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @retval None
  */
#define __HAL_DMAIdleReciever_CLEAR_NEFLAG(__HANDLE__) __HAL_DMAIdleReciever_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Clears the DMAIdleReciever ORE pending flag.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @retval None
  */
#define __HAL_DMAIdleReciever_CLEAR_OREFLAG(__HANDLE__) __HAL_DMAIdleReciever_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Clears the DMAIdleReciever IDLE pending flag.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @retval None
  */
#define __HAL_DMAIdleReciever_CLEAR_IDLEFLAG(__HANDLE__) __HAL_DMAIdleReciever_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Enable the specified DMAIdleReciever interrupt.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @param  __INTERRUPT__ specifies the DMAIdleReciever interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg DMAIdleReciever_IT_CTS:  CTS change interrupt
  *            @arg DMAIdleReciever_IT_LBD:  LIN Break detection interrupt
  *            @arg DMAIdleReciever_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg DMAIdleReciever_IT_TC:   Transmission complete interrupt
  *            @arg DMAIdleReciever_IT_RXNE: Receive Data register not empty interrupt
  *            @arg DMAIdleReciever_IT_IDLE: Idle line detection interrupt
  *            @arg DMAIdleReciever_IT_PE:   Parity Error interrupt
  *            @arg DMAIdleReciever_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_DMAIdleReciever_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((((__INTERRUPT__) >> 28U) == DMAIdleReciever_CR1_REG_INDEX)? ((__HANDLE__)->Instance->CR1 |= ((__INTERRUPT__) & DMAIdleReciever_IT_MASK)): \
                                                           (((__INTERRUPT__) >> 28U) == DMAIdleReciever_CR2_REG_INDEX)? ((__HANDLE__)->Instance->CR2 |= ((__INTERRUPT__) & DMAIdleReciever_IT_MASK)): \
                                                           ((__HANDLE__)->Instance->CR3 |= ((__INTERRUPT__) & DMAIdleReciever_IT_MASK)))

/** @brief  Disable the specified DMAIdleReciever interrupt.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @param  __INTERRUPT__ specifies the DMAIdleReciever interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg DMAIdleReciever_IT_CTS:  CTS change interrupt
  *            @arg DMAIdleReciever_IT_LBD:  LIN Break detection interrupt
  *            @arg DMAIdleReciever_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg DMAIdleReciever_IT_TC:   Transmission complete interrupt
  *            @arg DMAIdleReciever_IT_RXNE: Receive Data register not empty interrupt
  *            @arg DMAIdleReciever_IT_IDLE: Idle line detection interrupt
  *            @arg DMAIdleReciever_IT_PE:   Parity Error interrupt
  *            @arg DMAIdleReciever_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_DMAIdleReciever_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((((__INTERRUPT__) >> 28U) == DMAIdleReciever_CR1_REG_INDEX)? ((__HANDLE__)->Instance->CR1 &= ~((__INTERRUPT__) & DMAIdleReciever_IT_MASK)): \
                                                           (((__INTERRUPT__) >> 28U) == DMAIdleReciever_CR2_REG_INDEX)? ((__HANDLE__)->Instance->CR2 &= ~((__INTERRUPT__) & DMAIdleReciever_IT_MASK)): \
                                                           ((__HANDLE__)->Instance->CR3 &= ~ ((__INTERRUPT__) & DMAIdleReciever_IT_MASK)))

/** @brief  Checks whether the specified DMAIdleReciever interrupt source is enabled or not.
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         DMAIdleReciever Handle selects the USARTx or DMAIdleRecievery peripheral
  *         (USART,DMAIdleReciever availability and x,y values depending on device).
  * @param  __IT__ specifies the DMAIdleReciever interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg DMAIdleReciever_IT_CTS: CTS change interrupt (not available for DMAIdleReciever4 and DMAIdleReciever5)
  *            @arg DMAIdleReciever_IT_LBD: LIN Break detection interrupt
  *            @arg DMAIdleReciever_IT_TXE: Transmit Data Register empty interrupt
  *            @arg DMAIdleReciever_IT_TC:  Transmission complete interrupt
  *            @arg DMAIdleReciever_IT_RXNE: Receive Data register not empty interrupt
  *            @arg DMAIdleReciever_IT_IDLE: Idle line detection interrupt
  *            @arg DMAIdleReciever_IT_ERR: Error interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_DMAIdleReciever_GET_IT_SOURCE(__HANDLE__, __IT__) (((((__IT__) >> 28U) == DMAIdleReciever_CR1_REG_INDEX)? (__HANDLE__)->Instance->CR1:(((((uint32_t)(__IT__)) >> 28U) == DMAIdleReciever_CR2_REG_INDEX)? \
                                                       (__HANDLE__)->Instance->CR2 : (__HANDLE__)->Instance->CR3)) & (((uint32_t)(__IT__)) & DMAIdleReciever_IT_MASK))

/** @brief  Enable CTS flow control
  * @note   This macro allows to enable CTS hardware flow control for a given DMAIdleReciever instance,
  *         without need to call HAL_DMAIdleReciever_Init() function.
  *         As involving direct access to DMAIdleReciever registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying CTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - DMAIdleReciever instance should have already been initialised (through call of HAL_DMAIdleReciever_Init() )
  *           - macro could only be called when corresponding DMAIdleReciever instance is disabled (i.e __HAL_DMAIdleReciever_DISABLE(__HANDLE__))
  *             and should be followed by an Enable macro (i.e __HAL_DMAIdleReciever_ENABLE(__HANDLE__)).
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         The Handle Instance can be any USARTx (supporting the HW Flow control feature).
  *         It is used to select the USART peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_DMAIdleReciever_HWCONTROL_CTS_ENABLE(__HANDLE__)        \
  do{                                                      \
    ATOMIC_SET_BIT((__HANDLE__)->Instance->CR3, USART_CR3_CTSE);  \
    (__HANDLE__)->Init.HwFlowCtl |= USART_CR3_CTSE;        \
  } while(0U)

/** @brief  Disable CTS flow control
  * @note   This macro allows to disable CTS hardware flow control for a given DMAIdleReciever instance,
  *         without need to call HAL_DMAIdleReciever_Init() function.
  *         As involving direct access to DMAIdleReciever registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying CTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - DMAIdleReciever instance should have already been initialised (through call of HAL_DMAIdleReciever_Init() )
  *           - macro could only be called when corresponding DMAIdleReciever instance is disabled (i.e __HAL_DMAIdleReciever_DISABLE(__HANDLE__))
  *             and should be followed by an Enable macro (i.e __HAL_DMAIdleReciever_ENABLE(__HANDLE__)).
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         The Handle Instance can be any USARTx (supporting the HW Flow control feature).
  *         It is used to select the USART peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_DMAIdleReciever_HWCONTROL_CTS_DISABLE(__HANDLE__)        \
  do{                                                       \
    ATOMIC_CLEAR_BIT((__HANDLE__)->Instance->CR3, USART_CR3_CTSE); \
    (__HANDLE__)->Init.HwFlowCtl &= ~(USART_CR3_CTSE);      \
  } while(0U)

/** @brief  Enable RTS flow control
  *         This macro allows to enable RTS hardware flow control for a given DMAIdleReciever instance,
  *         without need to call HAL_DMAIdleReciever_Init() function.
  *         As involving direct access to DMAIdleReciever registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying RTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - DMAIdleReciever instance should have already been initialised (through call of HAL_DMAIdleReciever_Init() )
  *           - macro could only be called when corresponding DMAIdleReciever instance is disabled (i.e __HAL_DMAIdleReciever_DISABLE(__HANDLE__))
  *             and should be followed by an Enable macro (i.e __HAL_DMAIdleReciever_ENABLE(__HANDLE__)).
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         The Handle Instance can be any USARTx (supporting the HW Flow control feature).
  *         It is used to select the USART peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_DMAIdleReciever_HWCONTROL_RTS_ENABLE(__HANDLE__)       \
  do{                                                     \
    ATOMIC_SET_BIT((__HANDLE__)->Instance->CR3, USART_CR3_RTSE); \
    (__HANDLE__)->Init.HwFlowCtl |= USART_CR3_RTSE;       \
  } while(0U)

/** @brief  Disable RTS flow control
  *         This macro allows to disable RTS hardware flow control for a given DMAIdleReciever instance,
  *         without need to call HAL_DMAIdleReciever_Init() function.
  *         As involving direct access to DMAIdleReciever registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying RTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - DMAIdleReciever instance should have already been initialised (through call of HAL_DMAIdleReciever_Init() )
  *           - macro could only be called when corresponding DMAIdleReciever instance is disabled (i.e __HAL_DMAIdleReciever_DISABLE(__HANDLE__))
  *             and should be followed by an Enable macro (i.e __HAL_DMAIdleReciever_ENABLE(__HANDLE__)).
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  *         The Handle Instance can be any USARTx (supporting the HW Flow control feature).
  *         It is used to select the USART peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_DMAIdleReciever_HWCONTROL_RTS_DISABLE(__HANDLE__)       \
  do{                                                      \
    ATOMIC_CLEAR_BIT((__HANDLE__)->Instance->CR3, USART_CR3_RTSE);\
    (__HANDLE__)->Init.HwFlowCtl &= ~(USART_CR3_RTSE);     \
  } while(0U)

/** @brief  Macro to enable the DMAIdleReciever's one bit sample method
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  * @retval None
  */
#define __HAL_DMAIdleReciever_ONE_BIT_SAMPLE_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3|= USART_CR3_ONEBIT)

/** @brief  Macro to disable the DMAIdleReciever's one bit sample method
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  * @retval None
  */
#define __HAL_DMAIdleReciever_ONE_BIT_SAMPLE_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3\
                                                       &= (uint16_t)~((uint16_t)USART_CR3_ONEBIT))

/** @brief  Enable DMAIdleReciever
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  * @retval None
  */
#define __HAL_DMAIdleReciever_ENABLE(__HANDLE__)               ((__HANDLE__)->Instance->CR1 |=  USART_CR1_UE)

/** @brief  Disable DMAIdleReciever
  * @param  __HANDLE__ specifies the DMAIdleReciever Handle.
  * @retval None
  */
#define __HAL_DMAIdleReciever_DISABLE(__HANDLE__)              ((__HANDLE__)->Instance->CR1 &=  ~USART_CR1_UE)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DMAIdleReciever_Exported_Functions
  * @{
  */

/** @addtogroup DMAIdleReciever_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_DMAIdleReciever_Init(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_HalfDuplex_Init(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_LIN_Init(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint32_t BreakDetectLength);
HAL_StatusTypeDef HAL_MultiProcessor_Init(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint8_t Address, uint32_t WakeUpMethod);
HAL_StatusTypeDef HAL_DMAIdleReciever_DeInit(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_MspInit(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_MspDeInit(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);

/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_DMAIdleReciever_RegisterCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, HAL_DMAIdleReciever_CallbackIDTypeDef CallbackID,
                                            pDMAIdleReciever_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_DMAIdleReciever_UnRegisterCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, HAL_DMAIdleReciever_CallbackIDTypeDef CallbackID);

HAL_StatusTypeDef HAL_DMAIdleReciever_RegisterRxEventCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, pDMAIdleReciever_RxEventCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_DMAIdleReciever_UnRegisterRxEventCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
#endif /* USE_HAL_DMAIdleReciever_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup DMAIdleReciever_Exported_Functions_Group2 IO operation functions
  * @{
  */

/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_DMAIdleReciever_Transmit(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_DMAIdleReciever_Receive(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_DMAIdleReciever_Transmit_IT(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_DMAIdleReciever_Receive_IT(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_DMAIdleReciever_Transmit_DMA(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_DMAIdleReciever_Receive_DMA(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_DMAIdleReciever_DMAPause(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_DMAIdleReciever_DMAResume(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_DMAIdleReciever_DMAStop(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);

HAL_StatusTypeDef HAL_DMAIdleRecieverEx_ReceiveToIdle(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint8_t *pData, uint16_t Size, uint16_t *RxLen,
                                           uint32_t Timeout);
HAL_StatusTypeDef HAL_DMAIdleRecieverEx_ReceiveToIdle_IT(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_DMAIdleRecieverEx_ReceiveToIdle_DMA(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint8_t *pData, uint16_t Size);

HAL_DMAIdleReciever_RxEventTypeTypeDef HAL_DMAIdleRecieverEx_GetRxEventType(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);

/* Transfer Abort functions */
HAL_StatusTypeDef HAL_DMAIdleReciever_Abort(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_DMAIdleReciever_AbortTransmit(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_DMAIdleReciever_AbortReceive(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_DMAIdleReciever_Abort_IT(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_DMAIdleReciever_AbortTransmit_IT(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_DMAIdleReciever_AbortReceive_IT(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);

void HAL_DMAIdleReciever_IRQHandler(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_TxCpltCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_TxHalfCpltCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_RxCpltCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_RxHalfCpltCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_ErrorCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_AbortCpltCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_AbortTransmitCpltCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
void HAL_DMAIdleReciever_AbortReceiveCpltCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);

void HAL_DMAIdleRecieverEx_RxEventCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint16_t Size);

/**
  * @}
  */

/** @addtogroup DMAIdleReciever_Exported_Functions_Group3
  * @{
  */
/* Peripheral Control functions  ************************************************/
HAL_StatusTypeDef HAL_LIN_SendBreak(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_MultiProcessor_EnterMuteMode(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_MultiProcessor_ExitMuteMode(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
/**
  * @}
  */

/** @addtogroup DMAIdleReciever_Exported_Functions_Group4
  * @{
  */
/* Peripheral State functions  **************************************************/
HAL_DMAIdleReciever_StateTypeDef HAL_DMAIdleReciever_GetState(const DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
uint32_t              HAL_DMAIdleReciever_GetError(const DMAIdleReciever_HandleTypeDef *hDMAIdleReciever);
/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup DMAIdleReciever_Private_Constants DMAIdleReciever Private Constants
  * @{
  */
/** @brief DMAIdleReciever interruptions flag mask
  *
  */
#define DMAIdleReciever_IT_MASK                     0x0000FFFFU

#define DMAIdleReciever_CR1_REG_INDEX               1U
#define DMAIdleReciever_CR2_REG_INDEX               2U
#define DMAIdleReciever_CR3_REG_INDEX               3U
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DMAIdleReciever_Private_Macros DMAIdleReciever Private Macros
  * @{
  */
#define IS_DMAIdleReciever_WORD_LENGTH(LENGTH) (((LENGTH) == DMAIdleReciever_WORDLENGTH_8B) || \
                                     ((LENGTH) == DMAIdleReciever_WORDLENGTH_9B))
#define IS_DMAIdleReciever_LIN_WORD_LENGTH(LENGTH) (((LENGTH) == DMAIdleReciever_WORDLENGTH_8B))
#define IS_DMAIdleReciever_STOPBITS(STOPBITS) (((STOPBITS) == DMAIdleReciever_STOPBITS_1) || \
                                    ((STOPBITS) == DMAIdleReciever_STOPBITS_2))
#define IS_DMAIdleReciever_PARITY(PARITY) (((PARITY) == DMAIdleReciever_PARITY_NONE) || \
                                ((PARITY) == DMAIdleReciever_PARITY_EVEN) || \
                                ((PARITY) == DMAIdleReciever_PARITY_ODD))
#define IS_DMAIdleReciever_HARDWARE_FLOW_CONTROL(CONTROL)\
                              (((CONTROL) == DMAIdleReciever_HWCONTROL_NONE) || \
                               ((CONTROL) == DMAIdleReciever_HWCONTROL_RTS) || \
                               ((CONTROL) == DMAIdleReciever_HWCONTROL_CTS) || \
                               ((CONTROL) == DMAIdleReciever_HWCONTROL_RTS_CTS))
#define IS_DMAIdleReciever_MODE(MODE) ((((MODE) & 0x0000FFF3U) == 0x00U) && ((MODE) != 0x00U))
#define IS_DMAIdleReciever_STATE(STATE) (((STATE) == DMAIdleReciever_STATE_DISABLE) || \
                              ((STATE) == DMAIdleReciever_STATE_ENABLE))
#define IS_DMAIdleReciever_OVERSAMPLING(SAMPLING) (((SAMPLING) == DMAIdleReciever_OVERSAMPLING_16) || \
                                        ((SAMPLING) == DMAIdleReciever_OVERSAMPLING_8))
#define IS_DMAIdleReciever_LIN_OVERSAMPLING(SAMPLING) (((SAMPLING) == DMAIdleReciever_OVERSAMPLING_16))
#define IS_DMAIdleReciever_LIN_BREAK_DETECT_LENGTH(LENGTH) (((LENGTH) == DMAIdleReciever_LINBREAKDETECTLENGTH_10B) || \
                                                 ((LENGTH) == DMAIdleReciever_LINBREAKDETECTLENGTH_11B))
#define IS_DMAIdleReciever_WAKEUPMETHOD(WAKEUP) (((WAKEUP) == DMAIdleReciever_WAKEUPMETHOD_IDLELINE) || \
                                      ((WAKEUP) == DMAIdleReciever_WAKEUPMETHOD_ADDRESSMARK))
#define IS_DMAIdleReciever_BAUDRATE(BAUDRATE) ((BAUDRATE) <= 10500000U)
#define IS_DMAIdleReciever_ADDRESS(ADDRESS) ((ADDRESS) <= 0x0FU)

#define DMAIdleReciever_DIV_SAMPLING16(_PCLK_, _BAUD_)            ((uint32_t)((((uint64_t)(_PCLK_))*25U)/(4U*((uint64_t)(_BAUD_)))))
#define DMAIdleReciever_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (DMAIdleReciever_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define DMAIdleReciever_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((DMAIdleReciever_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (DMAIdleReciever_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U)\
                                                         + 50U) / 100U)
/* DMAIdleReciever BRR = mantissa + overflow + fraction
            = (DMAIdleReciever DIVMANT << 4) + (DMAIdleReciever DIVFRAQ & 0xF0) + (DMAIdleReciever DIVFRAQ & 0x0FU) */
#define DMAIdleReciever_BRR_SAMPLING16(_PCLK_, _BAUD_)            ((DMAIdleReciever_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (DMAIdleReciever_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U) + \
                                                        (DMAIdleReciever_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

#define DMAIdleReciever_DIV_SAMPLING8(_PCLK_, _BAUD_)             ((uint32_t)((((uint64_t)(_PCLK_))*25U)/(2U*((uint64_t)(_BAUD_)))))
#define DMAIdleReciever_DIVMANT_SAMPLING8(_PCLK_, _BAUD_)         (DMAIdleReciever_DIV_SAMPLING8((_PCLK_), (_BAUD_))/100U)
#define DMAIdleReciever_DIVFRAQ_SAMPLING8(_PCLK_, _BAUD_)         ((((DMAIdleReciever_DIV_SAMPLING8((_PCLK_), (_BAUD_)) - (DMAIdleReciever_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) * 100U)) * 8U)\
                                                         + 50U) / 100U)
/* DMAIdleReciever BRR = mantissa + overflow + fraction
            = (DMAIdleReciever DIVMANT << 4) + ((DMAIdleReciever DIVFRAQ & 0xF8) << 1) + (DMAIdleReciever DIVFRAQ & 0x07U) */
#define DMAIdleReciever_BRR_SAMPLING8(_PCLK_, _BAUD_)             ((DMAIdleReciever_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) << 4U) + \
                                                        ((DMAIdleReciever_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0xF8U) << 1U) + \
                                                        (DMAIdleReciever_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0x07U))

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup DMAIdleReciever_Private_Functions DMAIdleReciever Private Functions
  * @{
  */

HAL_StatusTypeDef DMAIdleReciever_Start_Receive_IT(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef DMAIdleReciever_Start_Receive_DMA(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint8_t *pData, uint16_t Size);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_DMAIdleReciever_H */

