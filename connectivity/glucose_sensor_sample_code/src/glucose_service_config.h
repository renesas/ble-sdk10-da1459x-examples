/**
 ****************************************************************************************
 *
 * @file glucose_service_config.h
 *
 * @brief Glucose service application configurations
 *
 * Copyright (C) 2015-2024 Renesas Electronics Corporation and/or its affiliates
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
# OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************************
 */

#ifndef GLUCOSE_SERVICE_CONFIG_H_
#define GLUCOSE_SERVICE_CONFIG_H_

/* Arbitrary application configurations settings. Normally, the following settings
 * should be adjusted based on application needs/capabilities. */

#define GLS_FLAGS_CONCENTRATION_TYPE_SAMPLE_LOCATION     ( 1 )
#define GLS_FLAGS_STATUS_ANNUNCIATION                    ( 1 )
#define GLS_FLAGS_CONTEXT_INFORMATION                    ( 1 )

#define GLS_FEATURE_INDICATION_PROPERTY                  ( 1 )
#define GLS_FEATURE_DEVICE_LOW_BATTERY                   ( 1 )
#define GLS_FEATURE_MULTIPLE_BOND                        ( 1 )

#define GLS_CONTEXT_FLAGS_CARBOHYDRATE_ID                ( 1 )

#define GLS_RACP_COMMAND_DELETE_STORED_RECORDS_SUPPORT   ( 1 )

#define GLS_RACP_OPERATOR_FIRST_RECORD_SUPPORT           ( 1 )
#define GLS_RACP_OPERATOR_LAST_RECORD_SUPPORT            ( 1 )

#define APP_DB_MAX_LIST_LEN                              50

#endif /* GLUCOSE_SERVICE_CONFIG_H_ */
