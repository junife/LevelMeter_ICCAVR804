#ifndef BUTTON_H
#define BUTTON_H

#include  "variables.h"

///////////////////////////////////////////////////////////////////////////////
// SVN: $LastChangedBy: DAK $
// SVN: $LastChangedDate: 2007-03-19 13:18:50 -0400 (Mon, 19 Mar 2007) $
// SVN: $Revision: 170 $
///////////////////////////////////////////////////////////////////////////////


typedef enum button_state_enum
{
   BUTTON_STATE_UNDEFINED,
   BUTTON_STATE_NOT_PRESSED,
   //BUTTON_STATE_NOT_PRESSED_HANDLED,
   //BUTTON_STATE_DEBOUNCE,
   BUTTON_STATE_PRESSED,
   //BUTTON_STATE_PRESSED_HANDLED,
   BUTTON_STATE_HELD,
   //BUTTON_STATE_HELD_HANDLED,
   BUTTON_STATE_RELEASED
} BUTTON_STATE_ENUM;

///////////////////////////////////////////////////////////////////////////////

typedef struct button_struct_t_tag
{
   BUTTON_STATE_ENUM  prevState;
   BUTTON_STATE_ENUM  state;
   
   u8            value;
   //timer_t     debounceTime;
   u16           holdTime;
   BOOL          heldFlag;
   BOOL          pressedFlag;
   BOOL          releasedFlag;
} BUTTON_STRUCT_T;


void Button_Scan(void);


extern BUTTON_STRUCT_T  button[2];
#endif