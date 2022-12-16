#include "C_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
/*
typedef struct _C_queue{
      int number;
      struct _C_queue* next;
}*C_queue;
*/
 
 
//初始化
static C_queue C_queue_init(/*C_queueOpertion* opertion*/)
{
      C_queue new_node = (C_queue)malloc(sizeof(struct _C_queue));
      if(new_node == NULL)
      {
            perror("new_node Init failed");
            return NULL;
      }
      //new_node->data = NULL;
      new_node->next = NULL;
/*
      if(opertion == NULL)
      {
            return NULL;
      }
      opertion->dequeue = C_queue_dequeue;
      opertion->enqueue = C_queue_enqueue;
      opertion->getHead = C_queue_getHead;
      opertion->getSize = C_queue_checkSize;
      opertion->showAll = C_queue_show;
*/
 
 
      return new_node;
}
 
//入队
static int C_queue_enqueue(C_queue head,C_queueData new_data)
{
      C_queue new_node = C_queue_init();
      if(new_node == NULL)
      {
            printf("new_node is failed\n");
            return -1;
      }
 
      new_node->data = new_data;
      if(head == NULL)
      {
            printf("head is null\n");
            return -2;
      }
      C_queue get_tail = head;
      for(;get_tail->next != NULL;
            get_tail = get_tail->next);
      
      new_node->next = get_tail->next;
      get_tail->next = new_node;
      return 0;
}
 
//读取头部
static C_queue_data C_queue_getHead(C_queue head)
{
      return &head->next->data;
}
 
//出队
static int C_queue_dequeue(C_queue head)
{
      if(head->next == NULL)
      {
            printf("this queue is null\n");
            return 1;
      }
 
      C_queue get_node = head->next;
      C_queue get_node_next = get_node->next;
 
      //get_node->next = get_node_next;
 
      head->next = get_node_next;
      //free(get_node->data);
      free(get_node);
 
      return 0;
}
 
static void C_queue_show(C_queue head,void (*shower_function)(C_queueData))
{
      if(head->next == NULL || head == NULL)
      {
            printf("this C_queue is NULL\n");
            return ;
      }
 
      C_queue shower = head->next;
      for(int i = 0;shower != NULL;
                  i++,shower = shower->next)
      {
            //printf("[%d]:[%d]\n",i,shower->data->number);
            shower_function(shower->data);
      }
}
 
 
//获取长度
static int C_queue_checkSize(C_queue head)
{
      if(head == NULL || head->next == NULL)
      {
            return -1;
      }
 
      C_queue getSize = head;
      int size = 0;
      for(;getSize->next != NULL;
      size++ ,getSize = getSize->next);
      return size;
 
}
 
static int C_queue_node_Init(C_queue_data _node)
{     
      if(_node == NULL)
            return -1;
 
      memset(_node,'\0',sizeof(C_queueData));
      return 0;
}
 
 
//获取指令
void get_C_queueOperation(C_queueOperation* operation)
{
      if(operation == NULL)
      {
            return;
      }
      operation->Init = C_queue_init;
      operation->dequeue = C_queue_dequeue;
      operation->enqueue = C_queue_enqueue;
      operation->getHead = C_queue_getHead;
      operation->getSize = C_queue_checkSize;
      operation->showAll = C_queue_show;
      operation->nodeInit = C_queue_node_Init;
}
