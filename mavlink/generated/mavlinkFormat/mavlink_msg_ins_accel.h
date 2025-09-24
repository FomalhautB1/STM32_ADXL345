#pragma once
// MESSAGE INS_ACCEL PACKING

#define MAVLINK_MSG_ID_INS_ACCEL 200


typedef struct __mavlink_ins_accel_t {
 uint64_t time_usec; /*<  Timestamp (µs)*/
 float x; /*<  Acceleration X (m/s²)*/
 float y; /*<  Acceleration Y (m/s²)*/
 float z; /*<  Acceleration Z (m/s²)*/
} mavlink_ins_accel_t;

#define MAVLINK_MSG_ID_INS_ACCEL_LEN 20
#define MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN 20
#define MAVLINK_MSG_ID_200_LEN 20
#define MAVLINK_MSG_ID_200_MIN_LEN 20

#define MAVLINK_MSG_ID_INS_ACCEL_CRC 31
#define MAVLINK_MSG_ID_200_CRC 31



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_INS_ACCEL { \
    200, \
    "INS_ACCEL", \
    4, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_ins_accel_t, time_usec) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_ins_accel_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_ins_accel_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_ins_accel_t, z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_INS_ACCEL { \
    "INS_ACCEL", \
    4, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_ins_accel_t, time_usec) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_ins_accel_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_ins_accel_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_ins_accel_t, z) }, \
         } \
}
#endif

/**
 * @brief Pack a ins_accel message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec  Timestamp (µs)
 * @param x  Acceleration X (m/s²)
 * @param y  Acceleration Y (m/s²)
 * @param z  Acceleration Z (m/s²)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ins_accel_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INS_ACCEL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, x);
    _mav_put_float(buf, 12, y);
    _mav_put_float(buf, 16, z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_INS_ACCEL_LEN);
#else
    mavlink_ins_accel_t packet;
    packet.time_usec = time_usec;
    packet.x = x;
    packet.y = y;
    packet.z = z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_INS_ACCEL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_INS_ACCEL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN, MAVLINK_MSG_ID_INS_ACCEL_LEN, MAVLINK_MSG_ID_INS_ACCEL_CRC);
}

/**
 * @brief Pack a ins_accel message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec  Timestamp (µs)
 * @param x  Acceleration X (m/s²)
 * @param y  Acceleration Y (m/s²)
 * @param z  Acceleration Z (m/s²)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ins_accel_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INS_ACCEL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, x);
    _mav_put_float(buf, 12, y);
    _mav_put_float(buf, 16, z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_INS_ACCEL_LEN);
#else
    mavlink_ins_accel_t packet;
    packet.time_usec = time_usec;
    packet.x = x;
    packet.y = y;
    packet.z = z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_INS_ACCEL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_INS_ACCEL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN, MAVLINK_MSG_ID_INS_ACCEL_LEN, MAVLINK_MSG_ID_INS_ACCEL_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN, MAVLINK_MSG_ID_INS_ACCEL_LEN);
#endif
}

/**
 * @brief Pack a ins_accel message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec  Timestamp (µs)
 * @param x  Acceleration X (m/s²)
 * @param y  Acceleration Y (m/s²)
 * @param z  Acceleration Z (m/s²)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ins_accel_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,float x,float y,float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INS_ACCEL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, x);
    _mav_put_float(buf, 12, y);
    _mav_put_float(buf, 16, z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_INS_ACCEL_LEN);
#else
    mavlink_ins_accel_t packet;
    packet.time_usec = time_usec;
    packet.x = x;
    packet.y = y;
    packet.z = z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_INS_ACCEL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_INS_ACCEL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN, MAVLINK_MSG_ID_INS_ACCEL_LEN, MAVLINK_MSG_ID_INS_ACCEL_CRC);
}

/**
 * @brief Encode a ins_accel struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param ins_accel C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ins_accel_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_ins_accel_t* ins_accel)
{
    return mavlink_msg_ins_accel_pack(system_id, component_id, msg, ins_accel->time_usec, ins_accel->x, ins_accel->y, ins_accel->z);
}

/**
 * @brief Encode a ins_accel struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ins_accel C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ins_accel_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_ins_accel_t* ins_accel)
{
    return mavlink_msg_ins_accel_pack_chan(system_id, component_id, chan, msg, ins_accel->time_usec, ins_accel->x, ins_accel->y, ins_accel->z);
}

/**
 * @brief Encode a ins_accel struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param ins_accel C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ins_accel_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_ins_accel_t* ins_accel)
{
    return mavlink_msg_ins_accel_pack_status(system_id, component_id, _status, msg,  ins_accel->time_usec, ins_accel->x, ins_accel->y, ins_accel->z);
}

/**
 * @brief Send a ins_accel message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec  Timestamp (µs)
 * @param x  Acceleration X (m/s²)
 * @param y  Acceleration Y (m/s²)
 * @param z  Acceleration Z (m/s²)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_ins_accel_send(mavlink_channel_t chan, uint64_t time_usec, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INS_ACCEL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, x);
    _mav_put_float(buf, 12, y);
    _mav_put_float(buf, 16, z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INS_ACCEL, buf, MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN, MAVLINK_MSG_ID_INS_ACCEL_LEN, MAVLINK_MSG_ID_INS_ACCEL_CRC);
#else
    mavlink_ins_accel_t packet;
    packet.time_usec = time_usec;
    packet.x = x;
    packet.y = y;
    packet.z = z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INS_ACCEL, (const char *)&packet, MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN, MAVLINK_MSG_ID_INS_ACCEL_LEN, MAVLINK_MSG_ID_INS_ACCEL_CRC);
#endif
}

/**
 * @brief Send a ins_accel message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_ins_accel_send_struct(mavlink_channel_t chan, const mavlink_ins_accel_t* ins_accel)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_ins_accel_send(chan, ins_accel->time_usec, ins_accel->x, ins_accel->y, ins_accel->z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INS_ACCEL, (const char *)ins_accel, MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN, MAVLINK_MSG_ID_INS_ACCEL_LEN, MAVLINK_MSG_ID_INS_ACCEL_CRC);
#endif
}

#if MAVLINK_MSG_ID_INS_ACCEL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_ins_accel_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, x);
    _mav_put_float(buf, 12, y);
    _mav_put_float(buf, 16, z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INS_ACCEL, buf, MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN, MAVLINK_MSG_ID_INS_ACCEL_LEN, MAVLINK_MSG_ID_INS_ACCEL_CRC);
#else
    mavlink_ins_accel_t *packet = (mavlink_ins_accel_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->x = x;
    packet->y = y;
    packet->z = z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INS_ACCEL, (const char *)packet, MAVLINK_MSG_ID_INS_ACCEL_MIN_LEN, MAVLINK_MSG_ID_INS_ACCEL_LEN, MAVLINK_MSG_ID_INS_ACCEL_CRC);
#endif
}
#endif

#endif

// MESSAGE INS_ACCEL UNPACKING


/**
 * @brief Get field time_usec from ins_accel message
 *
 * @return  Timestamp (µs)
 */
static inline uint64_t mavlink_msg_ins_accel_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field x from ins_accel message
 *
 * @return  Acceleration X (m/s²)
 */
static inline float mavlink_msg_ins_accel_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field y from ins_accel message
 *
 * @return  Acceleration Y (m/s²)
 */
static inline float mavlink_msg_ins_accel_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field z from ins_accel message
 *
 * @return  Acceleration Z (m/s²)
 */
static inline float mavlink_msg_ins_accel_get_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Decode a ins_accel message into a struct
 *
 * @param msg The message to decode
 * @param ins_accel C-struct to decode the message contents into
 */
static inline void mavlink_msg_ins_accel_decode(const mavlink_message_t* msg, mavlink_ins_accel_t* ins_accel)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    ins_accel->time_usec = mavlink_msg_ins_accel_get_time_usec(msg);
    ins_accel->x = mavlink_msg_ins_accel_get_x(msg);
    ins_accel->y = mavlink_msg_ins_accel_get_y(msg);
    ins_accel->z = mavlink_msg_ins_accel_get_z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_INS_ACCEL_LEN? msg->len : MAVLINK_MSG_ID_INS_ACCEL_LEN;
        memset(ins_accel, 0, MAVLINK_MSG_ID_INS_ACCEL_LEN);
    memcpy(ins_accel, _MAV_PAYLOAD(msg), len);
#endif
}
