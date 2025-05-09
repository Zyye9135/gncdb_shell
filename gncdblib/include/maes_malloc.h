/* 
 * 嵌入式系统内存分配组件
 * MAES: Memory Allocator for Embedded System 
 * 原位替换系统库malloc等函数
 * 暂不支持多任务保护，使用时注意
 */
#ifndef MAES_MALLOC_H_
#define MAES_MALLOC_H_

#include "oss_type_def.h"

#ifdef __cplusplus
extern "C" {
#endif


//处理编译警告时屏蔽
//#pragma comment(lib,"malloc_lib.lib")    // 工程代码目录下，拷贝对应规模的 malloc_lib.lib 文件；lib库文件都存放在malloc_lib目录下

/* 初始化，传入分配空间地址、大小 */
DT_VOID  s_maes_init(DT_VOID *vp_ptr, DT_UINT32 v_ui32_size);

/* malloc */
DT_VOID *s_maes_malloc(DT_UINT32 v_ui32_size);

/* calloc */
DT_VOID *s_maes_calloc(DT_UINT32 v_ui32_num, DT_UINT32 v_ui32_size);

/* realloc */
DT_VOID *s_maes_realloc(DT_VOID *vp_ptr, DT_UINT32 v_ui32_size);

/* free */
DT_VOID  s_maes_free(DT_VOID *vp_ptr);

#ifdef __cplusplus
}
#endif

#endif /* MAES_MALLOC_H_ */
