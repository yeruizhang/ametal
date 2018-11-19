#include "ametal.h"
#include "am_led.h"
#include "am_input.h"
#include "am_zm516x.h"
#include "model_bool.h"
#include "view_led.h"
#include "view_zigbee.h"
#include "app_mvc_bool_main.h"

static model_bool_t __g_model_bool;      			//����һ��������ʵ��
static void __input_key_proc (void *p_arg, int key_code, int key_state, int keep_time)
{
//    int       	code = (int)p_arg; 
    am_bool_t 	value;

    if (key_state == AM_INPUT_KEY_STATE_PRESSED) {
        if (model_bool_get(&__g_model_bool, &value) == 0) {
            model_bool_set(&__g_model_bool, !value);
        }
    }
}

int app_mvc_bool_main (int led_id, int key_code,am_zm516x_handle_t zm516x_handle)
{
    view_led_t              view_led0;     	//����һ��LED��ͼʵ��
    view_zigbee_t           view_zigbee;   	//����һ��zigbee��ͼʵ��
    am_input_key_handler_t   key_handler;   //����һ������������

    //ע�ᰴ���¼�����������Ӧ�ı���ͨ�����δ��ݸ��ص�����
    am_input_key_handler_register(&key_handler, __input_key_proc, (void *)key_code);
    //��ʼ��ģ��,value�ĳ�ֵΪAM_FALSE
    model_bool_init(&__g_model_bool, AM_FALSE);       
    //��ʼ����ͼʵ��
    view_led_init(&view_led0, led_id);
    view_zigbee_init(&view_zigbee, zm516x_handle);
    //������ͼ
    model_attach(&(__g_model_bool.isa), &(view_led0.isa));
    model_attach(&(__g_model_bool.isa), &(view_zigbee.isa));
    while (1) {
    }
//    return 0;
}
