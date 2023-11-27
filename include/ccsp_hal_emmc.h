/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**
* @file ccsp_hal_emmc.h
* @brief For CCSP Component: EMMC Status HAL Layer
*
*/

/**
 * @defgroup EMMC_HAL EMMC HAL
 *
 * EMMC HAL is used for the RDK-B EMMC Status abstraction layer.
 *
 * @defgroup EMMC_HAL_TYPES  EMMC HAL Data Types
 * @ingroup  EMMC_HAL
 *
 * @defgroup EMMC_HAL_APIS   EMMC HAL APIs
 * @ingroup  EMMC_HAL
 *
 **/

#ifndef __CCSP_HAL_EMMC_H__
#define __CCSP_HAL_EMMC_H__

#include <stdbool.h>

/**
 * @addtogroup EMMC_HAL_TYPES
 * @{
 */

/* Defines */
#define RDK_STMGR_MAX_DEVICES                        10 /**< Max number of Devices. */
#define RDK_STMGR_MAX_STRING_LENGTH                 128 /**< Max number of String length. */
#define RDK_STMGR_PARTITION_LENGTH                  256 /**< Partition length. */
#define RDK_STMGR_DIAGNOSTICS_LENGTH                256 /**< Diagnostics length. */
#define RDK_STMGR_DIAGNOSTICS_BLOB_LENGTH          2048 /**< Diagnostics blob length. */
#define RDK_STMGR_MAX_DIAGNOSTIC_ATTRIBUTES          20 /**< Max Number of SMART diagnostics attributes. */

/* Structs & Enums */
/**
 * @enum eSTMGRReturns
 * @brief List of ReturnCodes for EMMC API's Fetch Operation.
 */
typedef enum _stmgr_ReturnCode 
{
    RDK_STMGR_RETURN_SUCCESS = 0,          /**< Returns Success. */
    RDK_STMGR_RETURN_GENERIC_FAILURE = -1, /**< Returns Generic Failure. */
    RDK_STMGR_RETURN_INIT_FAILURE = -2,    /**< Returns Initialization Failure. */
    RDK_STMGR_RETURN_INVALID_INPUT = -3,   /**< Returns Invalid Input. */
    RDK_STMGR_RETURN_UNKNOWN_FAILURE = -4  /**< Returns Unknown Failure. */
} eSTMGRReturns;

/**
 * @enum eSTMGRDeviceType
 * @brief List of DeviceTypes supported.
 */
typedef enum _stmgr_DeviceType 
{
    RDK_STMGR_DEVICE_TYPE_HDD   = 0,    /**< Device type is HDD. */
    RDK_STMGR_DEVICE_TYPE_SDCARD = 1,   /**< Device type is SD Card. */
    RDK_STMGR_DEVICE_TYPE_USB = 2,      /**< Device type is USB. */
    RDK_STMGR_DEVICE_TYPE_FLASH = 3,    /**< Device type is Flash. */
    RDK_STMGR_DEVICE_TYPE_NVRAM = 4,    /**< Device type is NVRAM. */
    RDK_STMGR_DEVICE_TYPE_EMMCCARD = 5, /**< Device type is eMMC Card. */
    RDK_STMGR_DEVICE_TYPE_MAX = 6       /**< Device type is Max. */
} eSTMGRDeviceType;

/**
 * @enum eSTMGRDeviceStatus
 * @brief DeviceStatus List.
 */
typedef enum _stmgr_DeviceStatus 
{
    RDK_STMGR_DEVICE_STATUS_OK              = 0,          /**< Device Status is OK. */
    RDK_STMGR_DEVICE_STATUS_READ_ONLY       = (1 << 0),   /**< Device Status is Read Only. */
    RDK_STMGR_DEVICE_STATUS_NOT_PRESENT     = (1 << 1),   /**< Device Status is Not Present. */
    RDK_STMGR_DEVICE_STATUS_NOT_QUALIFIED   = (1 << 2),   /**< Device Status is Not Qualified. */
    RDK_STMGR_DEVICE_STATUS_DISK_FULL       = (1 << 3),   /**< Device Status is Disk Full. */
    RDK_STMGR_DEVICE_STATUS_READ_FAILURE    = (1 << 4),   /**< Device Status is Read Failure. */
    RDK_STMGR_DEVICE_STATUS_WRITE_FAILURE   = (1 << 5),   /**< Device Status is Write Failure. */
    RDK_STMGR_DEVICE_STATUS_UNKNOWN         = (1 << 6)    /**< Device Status is Unknown. */
} eSTMGRDeviceStatus;

/**
 * @enum eSTMGREvents
 * @brief Event Types List.
 */
typedef enum _stmgr_events 
{
    RDK_STMGR_EVENT_STATUS_CHANGED = 100, /**< Event is Status Changed. */
    RDK_STMGR_EVENT_HEALTH_WARNING = 101, /**< Event is Health Warning. */
    RDK_STMGR_EVENT_DEVICE_FAILURE = 102  /**< Event is Device Failure. */
} eSTMGREvents;

typedef struct _stmgr_DeviceIds {
    unsigned short m_numOfDevices;
    char m_deviceIDs[RDK_STMGR_MAX_DEVICES][RDK_STMGR_MAX_STRING_LENGTH];
} eSTMGRDeviceIDs;

typedef struct _stmgr_DeviceInfo {
    char m_deviceID[RDK_STMGR_MAX_STRING_LENGTH];         /**< The unique identifier or serial number of the EMMC device. It is a 128 byte character array. It is vendor 
							                                   specific. */
	
    eSTMGRDeviceType m_type;                              /**< It is type of the EMMC device, such as HDD, SDCARD, USB, etc. It is a variable is from the enumerated 
							                                   datatype eSTMGRDeviceType.
                                                               The range of acceptable values is 0 to 6 based on eSTMGRDeviceType enum type value. The enum 
							                                   eSTMGRDeviceType defined below.
                                                               RDK_STMGR_DEVICE_TYPE_HDD      = 0,
                                                               RDK_STMGR_DEVICE_TYPE_SDCARD   = 1,
                                                               RDK_STMGR_DEVICE_TYPE_USB      = 2,
                                                               RDK_STMGR_DEVICE_TYPE_FLASH    = 3,
                                                               RDK_STMGR_DEVICE_TYPE_NVRAM    = 4,
                                                               RDK_STMGR_DEVICE_TYPE_EMMCCARD = 5,
                                                               RDK_STMGR_DEVICE_TYPE_MAX      = 6 */

    unsigned long long m_capacity;                        /**< It is a unsigned long long. The value ranges from 0 to (2^32)-1. It is vendor specific. */
	
    eSTMGRDeviceStatus m_status;                          /**< This variable is from the enumerated datatype eSTMGRDeviceStatus.
                                                               The range of acceptable values is 0 to 6 based on eSTMGRDeviceType enum type value. The enum 
							                                   eSTMGRDeviceType defined below.
                                                               RDK_STMGR_DEVICE_STATUS_OK             = 0,
                                                               RDK_STMGR_DEVICE_STATUS_READ_ONLY      = (1 << 0), 1
                                                               RDK_STMGR_DEVICE_STATUS_NOT_PRESENT    = (1 << 1), 2
                                                               RDK_STMGR_DEVICE_STATUS_NOT_QUALIFIED  = (1 << 2), 4
                                                               RDK_STMGR_DEVICE_STATUS_DISK_FULL      = (1 << 3), 8
                                                               RDK_STMGR_DEVICE_STATUS_READ_FAILURE   = (1 << 4), 16
                                                               RDK_STMGR_DEVICE_STATUS_WRITE_FAILURE  = (1 << 5), 32
                                                               RDK_STMGR_DEVICE_STATUS_UNKNOWN        = (1 << 6)  64 */

    char m_partitions[RDK_STMGR_PARTITION_LENGTH];        /**< It is a 256 byte character array. It is vendor specific. */
	
    char m_manufacturer[RDK_STMGR_MAX_STRING_LENGTH];     /**< It is a 128 byte character array. It is vendor specific. */
	
    char m_model[RDK_STMGR_MAX_STRING_LENGTH];            /**< It is a 128 byte character array. It is vendor specific. */
	
    char m_serialNumber[RDK_STMGR_MAX_STRING_LENGTH];     /**< It is a 128 byte character array. It is vendor specific. */
	
    char m_firmwareVersion[RDK_STMGR_MAX_STRING_LENGTH];  /**< It is a 128 byte character array. It is vendor specific. */
	
    char m_hwVersion[RDK_STMGR_MAX_STRING_LENGTH];        /**< It is a 128 byte character array. It is vendor specific. */
	
    char m_ifATAstandard[RDK_STMGR_MAX_STRING_LENGTH];    /**< It is a 128 byte character array. It is vendor specific. */
	
    bool m_hasSMARTSupport;                               /**< It is a boolean. Possible values: true or false. */
	
} eSTMGRDeviceInfo;

typedef struct _stmgr_DeviceInfos {
    unsigned short m_numOfDevices;
    eSTMGRDeviceInfo m_devices[RDK_STMGR_MAX_DEVICES];
} eSTMGRDeviceInfoList;

typedef struct _stmgr_PartitionInfo {
    char m_partitionId [RDK_STMGR_MAX_STRING_LENGTH];
    char m_name [RDK_STMGR_MAX_STRING_LENGTH];
    char m_mountPath [RDK_STMGR_MAX_STRING_LENGTH];
    char m_format[RDK_STMGR_MAX_STRING_LENGTH];
    eSTMGRDeviceStatus m_status;
    unsigned long long m_capacity;
    unsigned long long m_freeSpace;
    bool m_isTSBSupported;
    bool m_isDVRSupported;
} eSTMGRPartitionInfo;

typedef struct _stmgr_DiagnosticsAttributes {
    char m_name[RDK_STMGR_MAX_STRING_LENGTH];   /*!< Gives SMART diagnostics attributes name. */
    char m_value[RDK_STMGR_MAX_STRING_LENGTH];  /*!< Gives SMART diagnostics attributes value, Comma separated. */
} eSTMGRDiagAttributes;

typedef struct _stmgr_DiagnosticsAttributeList {
    unsigned short m_numOfAttributes;
    eSTMGRDiagAttributes m_diagnostics[RDK_STMGR_MAX_DIAGNOSTIC_ATTRIBUTES];
} eSTMGRDiagAttributesList;

typedef struct _stmgr_Health {
    char m_deviceID[RDK_STMGR_MAX_STRING_LENGTH];               /**<  The unique identifier or serial number of the EMMC 
	                                                                  device. It is a 128 byte character array. It is vendor 
						                                              specific. */
																	 
    eSTMGRDeviceType m_deviceType;                              /**< It is type of the EMMC device, such as HDD, SDCARD, USB,
    	                                                             etc. It is a variable is from the enumerated datatype eSTMGRDeviceType.
                                                                     The range of acceptable values is 0 to 6 based on eSTMGRDeviceType enum 
				                                                     type value. The enum eSTMGRDeviceType defined below.
                                                                     RDK_STMGR_DEVICE_TYPE_HDD = 0,
                                                                     RDK_STMGR_DEVICE_TYPE_SDCARD = 1,
                                                                     RDK_STMGR_DEVICE_TYPE_USB = 2,
                                                                     RDK_STMGR_DEVICE_TYPE_FLASH = 3,
                                                                     RDK_STMGR_DEVICE_TYPE_NVRAM = 4,
                                                                     RDK_STMGR_DEVICE_TYPE_EMMCCARD = 5,
                                                                     RDK_STMGR_DEVICE_TYPE_MAX = 6 */
																	 
    bool m_isOperational;                                       /**< It is a boolean variable. Possible values: true or false. */
	
    bool m_isHealthy;                                           /**< It is a boolean variable. Possible values: true or false. */
	
    union {
        eSTMGRDiagAttributesList m_list;                        /**< The m_list is the object is from the structure eSTMGRDiagAttributesList.
                                                                     The members of the eSTMGRDiagAttributesList structure are defined below.
                                                                     m_numOfAttributes   -  It is a unsigned short. The value ranges from 0 to (2^16)-1. It is vendor 
								                                                            specific.
                                                                     m_diagnostics       -  It is a structure array of size 20 from the structure eSTMGRDiagAttributes.
                                                                        The members of the eSTMGRDiagAttributesList structure are defined below.
                                                                        m_name   -  It is a 128 byte character array. It is vendor specific.
                                                                        m_value  -  It is a 128 byte character array. It is vendor specific. */
																		
        char m_blob[RDK_STMGR_DIAGNOSTICS_BLOB_LENGTH];         /**< It is 2048 byte character array. It is vendor specific. */
    } m_diagnostics;
    eSTMGRDiagAttributesList m_lifetimesList;                    /**< This object is from the structure eSTMGRDiagAttributesList.
                                                                 The members of the eSTMGRDiagAttributesList structure are defined below.
                                                                  m_numOfAttributes   -  It is a unsigned short. The value ranges from 0 to (2^16)-1. It is vendor specific.
                                                                  m_diagnostics       -  It is a structure array of size 20 from the structure eSTMGRDiagAttributes.
                                                                     The members of the eSTMGRDiagAttributes structure are defined below.
                                                                     m_name   -  It is a 128 byte character array. It is vendor specific.
                                                                     m_value  -  It is a 128 byte character array. It is vendor specific. */

    eSTMGRDiagAttributesList m_firstExceededConfiguredLife;  /**< This object is from the structure eSTMGRDiagAttributesList.
                                                                  The members of the eSTMGRDiagAttributesList structure are defined below.
                                                                  m_numOfAttributes   -  It is a unsigned short. The value ranges from 0 to (2^16)-1. It is vendor specific.
                                                                  m_diagnostics       -  It is a structure array of size 20 from the structure eSTMGRDiagAttributes.
                                                                     The members of the eSTMGRDiagAttributes structure are defined below.
                                                                     m_name   -  It is a 128 byte character array. It is vendor specific.
                                                                     m_value  -  It is a 128 byte character array. It is vendor specific. */
																	 
    eSTMGRDiagAttributesList m_firstExceededMaxLife;         /**< This object is from the structure eSTMGRDiagAttributesList.
                                                                  The members of the eSTMGRDiagAttributesList structure are defined below.
                                                                  m_numOfAttributes   -  It is a unsigned short. The value ranges from 0 to (2^16)-1. It is vendor specific.
                                                                  m_diagnostics       -  It is a structure array of size 20 from the structure eSTMGRDiagAttributes.
                                                                     The members of the eSTMGRDiagAttributes structure are defined below.
                                                                     m_name   -  It is a 128 byte character array. It is vendor specific.
                                                                     m_value  -  It is a 128 byte character array. It is vendor specific. */
																	 
    eSTMGRDiagAttributesList m_healthStatesList;             /**< This object is from the structure eSTMGRDiagAttributesList.
                                                                  The members of the eSTMGRDiagAttributesList structure are defined below.
                                                                  m_numOfAttributes   -  It is a unsigned short. The value ranges from 0 to (2^16)-1. It is vendor specific.
                                                                  m_diagnostics       -  It is a structure array of size 20 from the structure eSTMGRDiagAttributes.
                                                                     The members of the eSTMGRDiagAttributes structure are defined below.
                                                                     m_name   -  It is a 128 byte character array. It is vendor specific.
                                                                     m_value  -  It is a 128 byte character array. It is vendor specific. */
} eSTMGRHealthInfo;

typedef struct _stmgr_EventMessage {
    eSTMGREvents m_eventType;
    char m_deviceID[RDK_STMGR_MAX_STRING_LENGTH];
    eSTMGRDeviceType m_deviceType;
    eSTMGRDeviceStatus m_deviceStatus;
    char m_description[RDK_STMGR_MAX_STRING_LENGTH];
    char m_diagnostics[RDK_STMGR_DIAGNOSTICS_LENGTH];
} eSTMGREventMessage;

typedef struct _stmgr_CallBackData{
   bool isSDCard;
   char mountPath[200];
}eSTMGRCallBackData;

/** @} */  //END OF GROUP EMMC_HAL_TYPES

//typedef void (*fnSTMGR_EventCallback)(eSTMGREventMessage*);

// HAL Functions

/**
 * @addtogroup EMMC_HAL_APIS
 * @{
 */

/* CcspHalEmmcGetHealthInfo() function */
/**
* @brief Provides EMMC health information
* @param[out] pHealthInfo - A Pointer to eSTMGRHealthInfo structure that needs to be updated.
*
* @return The status of the operation.
* @retval RDK_STMGR_RETURN_SUCCESS Success.
* @retval RDK_STMGR_RETURN_GENERIC_FAILURE Generic Failure.
* @retval RDK_STMGR_RETURN_INIT_FAILURE Initialization failure.
* @retval RDK_STMGR_RETURN_INVALID_INPUT Invalid Input.
* @retval RDK_STMGR_RETURN_UNKNOWN_FAILURE Unknown Failure.
* @remark The caller of this function is responsible for allocating memory for the eSTMGRHealthInfo structure.
*
*/
eSTMGRReturns CcspHalEmmcGetHealthInfo (eSTMGRHealthInfo* pHealthInfo);

/* CcspHalEmmcGetDeviceInfo() function */
/**
* @brief Provides EMMC Device information
* @param[out] pDeviceInfo - A Pointer to eSTMGRDeviceInfo structure that needs to be updated.
*
* @return The status of the operation.
* @retval RDK_STMGR_RETURN_SUCCESS Success.
* @retval RDK_STMGR_RETURN_GENERIC_FAILURE Generic Failure.
* @retval RDK_STMGR_RETURN_INIT_FAILURE Initialization failure.
* @retval RDK_STMGR_RETURN_INVALID_INPUT Invalid Input.
* @retval RDK_STMGR_RETURN_UNKNOWN_FAILURE Unknown Failure.
* @remark The caller of this function is responsible for allocating memory for the eSTMGRDeviceInfo structure.
*
*/
eSTMGRReturns CcspHalEmmcGetDeviceInfo (eSTMGRDeviceInfo* pDeviceInfo);

/** @} */  //END OF GROUP EMMC_HAL_APIS

#endif /* __CCSP_HAL_EMMC_H__ */

