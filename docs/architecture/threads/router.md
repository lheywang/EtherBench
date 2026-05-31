# Router

The router task is one of the most important one on the design. It's job is to push, in the right FIFO the incomming message.
It handle duplication of the data, as a message can have different destinations. In that case garbage collection is handled.

All messages are send on the following structure :

```c
typedef struct router_messge_t {
    ROUTER_SRC src;
    ROUTER_DEST dest;
    ROUTER_TYPE type;
    ROUTER_STATUS status;
    uint16_t size;
    ROUTER_PAYLOAD payload;
    ...
};
```

The different types are all enums, defined in the corresponding header file. The payload can be included in the header if small enough (< 16 bytes), 
or can be allocated on a TX_POOL, which is the recommended method.

Additionnaly, a response pointer function is passed, to ensure the command parser can respond while using the right tool, that correspond to the source.
This make the whole system agnostic to the source of the command.