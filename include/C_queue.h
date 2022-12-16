#pragma once
 
typedef struct {
       int number;
}C_queueData_message;
 
//data
typedef union _C_queue_data{
     C_queueData_message message;
}*C_queue_data,C_queueData;
 
//node
typedef struct _C_queue{
      //数据区
      C_queueData data;
      struct _C_queue* next;
}*C_queue;
 
 
/**
 * @file C_queue.h
 * @author C-Onely
 * @date 2021-12-20-14-25
 * @version 0.00.00.1
 * @brief 队列工具包
 * @details 
 * @param Init --------------初始化
 * @param enqueue ---------入队
 * @param getHead ---------读取头部数据
 * @param dequeue ---------出队
 * @param showAll ---------遍历展示
 * @param getSize ---------获取长度
 * @param nodeInit ---------初始化节点
 * @return 0：成功 -1：失败
 * @retval 返回一个整形数据
 **/
typedef struct _C_queue_opertion{
      C_queue (*Init)(void);
      //入队
      int (*enqueue)(C_queue,C_queueData);
      //读取头部数据
      C_queue_data (*getHead)(C_queue);
      //出队
      int (*dequeue)(C_queue);
      //遍历展示
      void (*showAll)(C_queue,void (*)(C_queueData));
      //获取长度
      int (*getSize)(C_queue);
      int (*nodeInit)(C_queue_data);
}C_queueOperation;
 
 
//获取指令
extern void get_C_queueOperation(C_queueOperation* operation);
 
 
