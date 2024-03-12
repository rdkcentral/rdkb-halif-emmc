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
 * The EMMC HAL (Hardware Abstraction Layer) is used in RDK-B (Reference Design Kit-Broadband) to provide an abstraction layer for EMMC (Embedded Multi-Media Controller) status.
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
 * @enum _stmgr_ReturnCode
 *
 * @brief List of ReturnCodes for EMMC API's Fetch Operation.
 */
typedef enum _stmgr_ReturnCode {
    RDK_STMGR_RETURN_SUCCESS = 0,          /**< Returns Success. */
    RDK_STMGR_RETURN_GENERIC_FAILURE = -1, /**< Returns Generic Failure. */
    RDK_STMGR_RETURN_INIT_FAILURE = -2,    /**< Returns Initialization Failure. */
    RDK_STMGR_RETURN_INVALID_INPUT = -3,   /**< Returns Invalid Input. */
    RDK_STMGR_RETURN_UNKNOWN_FAILURE = -4  /**< Returns Unknown Failure. */
} eSTMGRReturns;

/**
 * @enum _stmgr_DeviceType
 *
 * @brief List of DeviceTypes supported.
 */
typedef enum _stmgr_DeviceType {
    RDK_STMGR_DEVICE_TYPE_HDD   = 0,    /**< Device type is HDD. */
    RDK_STMGR_DEVICE_TYPE_SDCARD = 1,   /**< Device type is SD Card. */
    RDK_STMGR_DEVICE_TYPE_USB = 2,      /**< Device type is USB. */
    RDK_STMGR_DEVICE_TYPE_FLASH = 3,    /**< Device type is Flash. */
    RDK_STMGR_DEVICE_TYPE_NVRAM = 4,    /**< Device type is NVRAM. */
    RDK_STMGR_DEVICE_TYPE_EMMCCARD = 5, /**< Device type is eMMC Card. */
    RDK_STMGR_DEVICE_TYPE_MAX = 6       /**< Device type is Max. */
} eSTMGRDeviceType;

/**
 * @enum _stmgr_DeviceStatus
 *
 * @brief DeviceStatus List.
 */
typedef enum _stmgr_DeviceStatus {
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
 * @enum _stmgr_events
 *
 * @brief Event Types List.
 */
typedef enum _stmgr_events {
    RDK_STMGR_EVENT_STATUS_CHANGED = 100, /**< Event is Status Changed. */
    RDK_STMGR_EVENT_HEALTH_WARNING = 101, /**< Event is Health Warning. */
    RDK_STMGR_EVENT_DEVICE_FAILURE = 102  /**< Event is Device Failure. */
} eSTMGREvents;

typedef struct _stmgr_DeviceIds {
    unsigned short m_numOfDevices;                                        /**< It holds the count of how many device IDs are stored in the m_deviceIDs array. */
    char m_deviceIDs[RDK_STMGR_MAX_DEVICES][RDK_STMGR_MAX_STRING_LENGTH]; /**< The total number of device IDs that can be stored is limited by RDK_STMGR_MAX_DEVICES. */
} eSTMGRDeviceIDs;

typedef struct _stmgr_DeviceInfo {
    char m_deviceID[RDK_STMGR_MAX_STRING_LENGTH];         /**< To store the unique identifier or serial number of the EMMC device. */
    eSTMGRDeviceType m_type;                              /**< EMMC device, such as HDD, SDCARD, USB, etc. */
    unsigned long long m_capacity;                        /**< Representing the capacity of the device. The value is vendor-specific. */
    eSTMGRDeviceStatus m_status;                          /**< Representing the status of the device. */
    char m_partitions[RDK_STMGR_PARTITION_LENGTH];        /**< To store information about the partitions on the device. The details are vendor-specific. */
    char m_manufacturer[RDK_STMGR_MAX_STRING_LENGTH];     /**< To store the manufacturer's name of the device. */
    char m_model[RDK_STMGR_MAX_STRING_LENGTH];            /**< To store the model name of the device. */
    char m_serialNumber[RDK_STMGR_MAX_STRING_LENGTH];     /**< To store the serial number of the device. */
    char m_firmwareVersion[RDK_STMGR_MAX_STRING_LENGTH];  /**< To store the firmware version of the device. */
    char m_hwVersion[RDK_STMGR_MAX_STRING_LENGTH];        /**< To store the hardware version of the device. */
    char m_ifATAstandard[RDK_STMGR_MAX_STRING_LENGTH];    /**< To store information about the ATA standard the device conforms to. */
    bool m_hasSMARTSupport;                               /**< Indicating whether the device supports SMART (Self-Monitoring, Analysis, and Reporting Technology). */
} eSTMGRDeviceInfo;

typedef struct _stmgr_DeviceInfos {
    unsigned short m_numOfDevices;                     /**< It holds the count of how many device information entries are stored in the m_devices array. */
    eSTMGRDeviceInfo m_devices[RDK_STMGR_MAX_DEVICES]; /**< Each element of this array represents the information for a single device. */
} eSTMGRDeviceInfoList;

typedef struct _stmgr_PartitionInfo {
    char m_partitionId [RDK_STMGR_MAX_STRING_LENGTH];  /**< To store the unique identifier of the partition. */
    char m_name [RDK_STMGR_MAX_STRING_LENGTH];         /**< To store the name of the partition. */
    char m_mountPath [RDK_STMGR_MAX_STRING_LENGTH];    /**< To store the file system path where the partition is mounted. This path is used to access the contents of the partition in the file system. */
    char m_format[RDK_STMGR_MAX_STRING_LENGTH];        /**< To store the format of the partition, such as ext4, NTFS, FAT32, etc. */
    eSTMGRDeviceStatus m_status;                       /**< Defines different possible status, such as connected, disconnected, error, etc. */
    unsigned long long m_capacity;                     /**< Represents the total capacity of the partition in bytes. */
    unsigned long long m_freeSpace;                    /**< Represents the available free space on the partition in bytes. */
    bool m_isTSBSupported;                             /**< Indicates whether the partition supports Time-Shift Buffering (TSB). Possible values are true (supported) or false (not supported). */
    bool m_isDVRSupported;                             /**< Indicates whether the partition supports Digital Video Recording (DVR). Possible values are true (supported) or false (not supported). */
} eSTMGRPartitionInfo;

typedef struct _stmgr_DiagnosticsAttributes {
    char m_name[RDK_STMGR_MAX_STRING_LENGTH];   /*!< To store the name of the SMART (Self-Monitoring, Analysis, and Reporting Technology) diagnostic attribute. The name provides a way to identify the attribute. */
    char m_value[RDK_STMGR_MAX_STRING_LENGTH];  /*!< To store the value of the SMART diagnostic attribute. The value is represented as a comma-separated string, which may contain multiple pieces of information related to the attribute. */
} eSTMGRDiagAttributes;

typedef struct _stmgr_DiagnosticsAttributeList {
    unsigned short m_numOfAttributes;                                        /**< It holds the count of how many attributes are stored in the m_diagnostics array. */
    eSTMGRDiagAttributes m_diagnostics[RDK_STMGR_MAX_DIAGNOSTIC_ATTRIBUTES]; /**< Each element of this array represents a diagnostic attribute.  */
} eSTMGRDiagAttributesList;

typedef struct _stmgr_Health {
    char m_deviceID[RDK_STMGR_MAX_STRING_LENGTH];               /**< To store the unique identifier or serial number of the EMMC device. The identifier is vendor-specific and is a 128-byte character array. */														 
    eSTMGRDeviceType m_deviceType;                              /**< This represents the type of the EMMC device, such as HDD, SDCARD, USB, etc. The eSTMGRDeviceType is an enumerated datatype that defines different possible device types. */															 
    bool m_isOperational;                                       /**< Indicates whether the device is operational. Possible values are true (operational) or false (not operational). */
    bool m_isHealthy;                                           /**< Indicates whether the device is healthy. Possible values are true (healthy) or false (not healthy). */
    union {
        eSTMGRDiagAttributesList m_list;                        																	
        char m_blob[RDK_STMGR_DIAGNOSTICS_BLOB_LENGTH];         
    } m_diagnostics;                                             /**< To store diagnostic attributes, while m_blob is a vendor-specific diagnostic information array. */
    eSTMGRDiagAttributesList m_lifetimesList;                    /**< To store a list of attributes related to the lifetimes of the device. */
    eSTMGRDiagAttributesList m_firstExceededConfiguredLife;      /**< To store attributes related to the first time the device exceeded its configured lifetime. */	 
    eSTMGRDiagAttributesList m_firstExceededMaxLife;             /**< To store attributes related to the first time the device exceeded its maximum lifetime. */																 
    eSTMGRDiagAttributesList m_healthStatesList;                 /**< To store a list of attributes related to the health states of the device. */
} eSTMGRHealthInfo;

typedef struct _stmgr_EventMessage {
    eSTMGREvents m_eventType;                         /**< The eSTMGREvents type would typically be an enumeration defining different possible events, such as device insertion, removal, error, etc. */
    char m_deviceID[RDK_STMGR_MAX_STRING_LENGTH];     /**< To store the unique identifier of the device associated with the event. */
    eSTMGRDeviceType m_deviceType;                    /**< The eSTMGRDeviceType would typically be an enumeration defining different possible device types, such as USB, SD card, HDD, etc. */
    eSTMGRDeviceStatus m_deviceStatus;                /**< The eSTMGRDeviceStatus would typically be an enumeration defining different possible device statuses, such as connected, disconnected, error, etc. */
    char m_description[RDK_STMGR_MAX_STRING_LENGTH];  /**< To store a textual description of the event, providing additional details or context. */
    char m_diagnostics[RDK_STMGR_DIAGNOSTICS_LENGTH]; /**< To store diagnostic information related to the event, which can be useful for troubleshooting or logging purposes. */
} eSTMGREventMessage;

typedef struct _stmgr_CallBackData{
   bool isSDCard;       /**< This indicates whether the device associated with the callback data is an SD card. If true, the device is an SD card; if false, it is not an SD card. */
   char mountPath[200]; /**< This path is used to access the contents of the device in the file system. */
}eSTMGRCallBackData;

/** @} */  //END OF GROUP EMMC_HAL_TYPES

//typedef void (*fnSTMGR_EventCallback)(eSTMGREventMessage*);

// HAL Functions

/*
 * TODO: Extend the return codes by listing out the possible reasons of failure, to improve the interface in the future. This was reported during the review for header file migration to opensource github.
 *
 */

/**
 * @addtogroup EMMC_HAL_APIS
 * @{
 */

/**
* @brief Provides EMMC health information
* @param[out] pHealthInfo - A pointer to a structure is used to access and update the health information of a device.
*
* @returns eSTMGRReturns
* @retval RDK_STMGR_RETURN_SUCCESS - on Success,
* @retval RDK_STMGR_RETURN_GENERIC_FAILURE - Generic Failure.
* @retval RDK_STMGR_RETURN_INIT_FAILURE - Initialization Failure.
* @retval RDK_STMGR_RETURN_INVALID_INPUT - Invalid Input.
* @retval RDK_STMGR_RETURN_UNKNOWN_FAILURE - Unknown Failure. 
*
*/
eSTMGRReturns CcspHalEmmcGetHealthInfo (eSTMGRHealthInfo* pHealthInfo);

/**
* @brief Provides EMMC Device information
* @param[out] pDeviceInfo - A pointer to a structure, the function will then update this structure with the device information of the EMMC device.
*
* @returns eSTMGRReturns
* @retval RDK_STMGR_RETURN_SUCCESS - on Success,
* @retval RDK_STMGR_RETURN_GENERIC_FAILURE - Generic Failure.
* @retval RDK_STMGR_RETURN_INIT_FAILURE - Initialization Failure.
* @retval RDK_STMGR_RETURN_INVALID_INPUT - Invalid Input.
* @retval RDK_STMGR_RETURN_UNKNOWN_FAILURE - Unknown Failure.
*
*/
eSTMGRReturns CcspHalEmmcGetDeviceInfo (eSTMGRDeviceInfo* pDeviceInfo);

/** @} */  //END OF GROUP EMMC_HAL_APIS

#endif /* __CCSP_HAL_EMMC_H__ */

