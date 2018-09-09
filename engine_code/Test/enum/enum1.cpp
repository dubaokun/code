    
    
    
 typedef enum {
            UNKNOWN = 0,
            UINT8 = 1,
            INT8 = 2,
            UINT16 = 3,
            INT16 = 4,
            UINT32 = 5,
            INT32 = 6,
            UINT64 = 7,
            INT64 = 8,
            FLOAT = 9,
            DOUBLE = 10,
            BOOL = 11,
        } E_TYPE;

        template <typename T>
            struct TypeEnum
            {
                enum { Val = UNKNOWN };
            };

        template <>
            struct TypeEnum<uint8_t>
            {
                enum { Val = UINT8 };
            };

        template <>
            struct TypeEnum<int8_t>
            {
                enum { Val = INT8 };
            };

        template <>
            struct TypeEnum<uint16_t>
            {
                enum { Val = UINT16 };
            };

        template <>
            struct TypeEnum<int16_t>
            {
                enum { Val = INT16 };
            };

        template <>
            struct TypeEnum<uint32_t>
            {
                enum { Val = UINT32 };
            };

        template <>
            struct TypeEnum<int32_t>
            {
                enum { Val = INT32 };
            };

        template <>
            struct TypeEnum<uint64_t>
            {
                enum { Val = UINT64 };
            };

        template <>
            struct TypeEnum<int64_t>
            {
                enum { Val = INT64 };
            };

        template <>
            struct TypeEnum<float>
            {
                enum { Val = FLOAT };
            };

        template <>
            struct TypeEnum<double>
            {
                enum { Val = DOUBLE };
            };

        template <>
            struct TypeEnum<bool>
            {
                enum { Val = BOOL};
            };
