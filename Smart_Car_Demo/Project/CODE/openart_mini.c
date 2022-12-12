#include "openart_mini.h"




uint8               openart_rx_buffer;
lpuart_transfer_t   openart_receivexfer;
lpuart_handle_t     openart_g_lpuartHandle;



void openart_uart1_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        //openart_rx_buffer;    //�����յ����ݺ���Զ����뵽���Ȼ���ȡopenart_rx_buffer�������ɶ�ȡ�����յ�������
    }
    
    handle->rxDataSize = openart_receivexfer.dataSize;  //��ԭ����������
    handle->rxData = openart_receivexfer.data;          //��ԭ��������ַ
}












void openart_mini(void)
{
    uart_init(USART_4, 115200, UART4_TX_C16, UART4_RX_C17);
    
    //���ô��ڽ��յĻ�����������������
    openart_receivexfer.dataSize = 1;
    openart_receivexfer.data = &openart_rx_buffer;
    
    //�����жϺ����������
    uart_set_handle(USART_4, &openart_g_lpuartHandle, openart_uart1_callback, NULL, 0, openart_receivexfer.data, 1);
    
    NVIC_SetPriority(LPUART4_IRQn, 14);         //���ô����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
    uart_rx_irq(USART_4, 1);
}