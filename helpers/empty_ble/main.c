#include "osal.h"

int main(void)
{
	OS_TASK_SCHEDULER_RUN();
}

OS_APP_MALLOC_FAILED(void)
{
	ASSERT_ERROR(0);
}

OS_APP_IDLE(void)
{
}

OS_APP_STACK_OVERFLOW(OS_TASK pxTask, char * pcTaskName)
{
	ASSERT_ERROR(0);
}

OS_APP_TICK(void)
{
}
