/*
 * lib_curve.c
 *
 *  Created on: Jul 6, 2021
 *      Author: williamhsu
 */

#include "lib_math.h"
uint32 Basic_T_curve_Pulsecmd(float32 S_max,float32 V_init,float32 V_max,float32 A_max,float32 Ploop_freqency)
{
	static uint32 Interval_state;
	static float32 t = 0;
	static float32 S_t,S_t_init,S_t_Virtual,S_t_difference;
    static float32 V_t,V_t_init,V_t_Virtual;
    //static float32 A_t,A_t_init;
    static float32 t_old[3];
    static float32 S_t_old[3];
    static float32 V_t_old[3];

    t=t+((float32) 1/Ploop_freqency);


    switch(Interval_state){
    case 0:
        //A_t = A_max;
    	if(V_init<V_max)
    	    V_t_init = V_init;
    	else
    	    V_t_init = V_max;

        V_t_init = V_init;
        V_t = A_max*t+ V_t_init;

        S_t = 0.5*t*t*A_max+V_t_init*t;
        V_t_Virtual =  A_max*(t+0.0002);
        S_t_Virtual =  0.5*(t+0.0002)*(t+0.0002)*A_max+V_t_init*(t+0.0002);
        if(S_t_Virtual>0.25*S_max || V_t_Virtual >V_max)
            Interval_state = 1;

        S_t_old[0] = S_t;
        V_t_old[0] = V_t;
        t_old[0] = t;
        S_t_difference =  0.25*S_max-S_t_old[0];

        break;
    case 1:
        //A_t = 0;

        V_t = V_t_old[0];

        S_t_init = S_t_old[0]-t_old[0]*V_t_old[0];
        S_t = t*V_t_old[0]+S_t_init;
        S_t_Virtual =  (t+0.0002)*V_t_old[0]+S_t_init;
        if(S_t_Virtual>(0.75*S_max+S_t_difference))
            Interval_state = 2;

        S_t_old[1] = S_t;
        V_t_old[1] = V_t;
        t_old[1] = t;

        break;
    case 2:
        //A_t = -A_max;

        V_t_init = V_t_old[1]+A_max*t_old[1];
        V_t = -A_max*t+V_t_init;

        S_t_init = S_t_old[1]-(-0.5*t_old[1]*t_old[1]*A_max+t_old[1]*V_t_init);

        S_t = -0.5*t*t*A_max+t*V_t_init+S_t_init;

        if(S_t>S_max||t>t_old[1] +t_old[0]){
            Interval_state = 3;
        }
        S_t_old[2] = S_t;
        V_t_old[2] = V_t;
        t_old[2] = t;


        break;
    case 3:
        /*if(S_t<S_max)
        	V_t = 1.0;
        else if(S_t >S_max)
            V_t = -1.0;
        else
            V_t = 0;
    	S_t_init = S_t_old[2]-t_old[2]*V_t;
    	S_t = t* V_t+S_t_init;
    	if(S_t>S_max)
    	    Interval_state = 4;*/
    	S_t = S_max;
        break;
    default:
        break;
    }



    return ((uint32)(S_t));
}
uint32 Basic_S_curve_Pulsecmd(float32 S_max,float32 V_init,float32 V_max,float32 J_max,float32 Ploop_freqency)
{
	static float32 V_acc;
	static uint32 Interval_state,counter;
	static float32 t = 0;
	static float32 S_t,S_t_init,S_t_Virtual;
    static float32 V_t,V_t_init,V_t_Virtual;
    static float32 A_t,A_t_init,A_t_Virtual;
    //static float32 J_t;
    static float32 t_old[7];
    static float32 S_t_old[7];
    static float32 V_t_old[7];
    static float32 A_t_old[7];

    if(V_init> V_max)
        V_t_init = V_max;
    else
        V_t_init = V_init;
     V_acc = (V_max-V_init)/3;

   switch(Interval_state){
    case 0:
        //J_t = J_max;
        A_t = J_max*t;
        V_t = 0.5*J_max*t*t+V_t_init;
        S_t = J_max*t*t*t/6+t*V_t_init;

        S_t_old[0] = S_t;
        V_t_old[0] = V_t;
        A_t_old[0] = A_t;
        t_old[0] = t;

        V_t_Virtual =  0.5*J_max*(t+0.0002)*(t+0.0002)+V_t_init;
        S_t_Virtual =  J_max*(t+0.0002)*(t+0.0002)*(t+0.0002)/6+(t+0.0002)*V_t_init;

        if(V_t_Virtual>(V_t_init+V_acc)||S_t_Virtual>S_max/54)
        {
            Interval_state++;
        }
        break;
    case 1:
        //J_t = 0;
        A_t =  A_t_old[0];

        //A_t_old[0]*t_old[0] +V_t_init=V_t_old[0]
        V_t_init = V_t_old[0]-A_t_old[0]*t_old[0];
        V_t =  A_t_old[0]*t+V_t_init;

        //0.5*A_t_old[0]*t_old[0]*t_old[0]+t_old[0]*V_t_init+S_t_init=S_t_old[0]
        S_t_init=S_t_old[0]-(0.5*A_t_old[0]*t_old[0]*t_old[0]+t_old[0]*V_t_init);
        S_t = 0.5*A_t_old[0]*t*t+t*V_t_init+S_t_init;

        S_t_old[1] = S_t;
        V_t_old[1] = V_t;
        A_t_old[1] = A_t;
        t_old[1] = t;

        V_t_Virtual = A_t_old[0]*(t+0.0002)+V_t_init;
        S_t_Virtual = 0.5*A_t_old[0]*(t+0.0002)*(t+0.0002)+(t+0.0002)*V_t_init+S_t_init;
        if(V_t_Virtual>(V_max-V_acc)||S_t_Virtual>11*S_max/108 )
        {
            Interval_state++;
        }
        break;
      case 2:
        //J_t = -J_max;
        //-J_max*t_old[1]+A_t_init = A_t_old[1]
        A_t_init = A_t_old[1]+J_max*t_old[1];
        A_t = -J_max*t+A_t_init;

        //-0.5*J_max*t_old[1]*t_old[1]+A_t_init*t_old[1]+V_t_init=V_t_old[1];
        V_t_init = V_t_old[1]-(-0.5*J_max*t_old[1]*t_old[1]+A_t_init*t_old[1]);
        V_t =  -0.5*J_max*t*t+A_t_init*t+V_t_init;

        // -J_max* t_old[1]* t_old[1]* t_old[1]/6+0.5*A_t_init* t_old[1]* t_old[1]+V_t_init* t_old[1]+S_t_init=S_t_old[1]
        S_t_init=S_t_old[1]-(-J_max* t_old[1]* t_old[1]* t_old[1]/6+0.5*A_t_init* t_old[1]* t_old[1]+V_t_init* t_old[1]);
        S_t =  -J_max*t*t*t/6+0.5*A_t_init*t*t+V_t_init*t+S_t_init;

        S_t_old[2] = S_t;
        V_t_old[2] = V_t;
        A_t_old[2] = A_t;
        t_old[2] = t;

        V_t_Virtual = -0.5*J_max*(t+0.0002)*(t+0.0002)+A_t_init*(t+0.0002)+V_t_init;
        S_t_Virtual =-J_max*(t+0.0002)*(t+0.0002)*(t+0.0002)/6+0.5*A_t_init*(t+0.0002)*(t+0.0002)+V_t_init*(t+0.0002)+S_t_init;
        A_t_Virtual = -J_max*(t+0.0002)+A_t_init;
        if(V_t_Virtual>V_max || S_t_Virtual>S_max/4 || A_t_Virtual <0)
        {
            Interval_state++;
        }
        break;
     case 3:
        //J_t = 0;
        A_t = 0;

        //A_t_old[2]* t_old[2]+V_t_init=V_t_old[2]
        V_t_init = V_t_old[2];
        V_t = V_t_init;

        //V_t_init*t_old[2]+S_t_init=S_t_old[2]
        S_t_init=S_t_old[2]-V_t_init*t_old[2];

        S_t = V_t_init*t+S_t_init;

        S_t_old[3] = S_t;
        V_t_old[3] = V_t;
        A_t_old[3] = A_t;
        t_old[3] = t;

        S_t_Virtual = V_t_init*(t+0.0002)+S_t_init;

        if(S_t_Virtual>(0.75*S_max))
        {
            Interval_state++;
        }
        break;
      case 4:
        //J_t = -J_max;
        //-J_max*t_old[3] +A_t_init = A_t_old[3]
        A_t_init = A_t_old[3]+J_max*t_old[3];
        A_t = -J_max*t+A_t_init;

        //-0.5*J_max*t_old[3] *t_old[3] +A_t_init*t_old[3] +V_t_init = V_t_old[3];
        V_t_init = V_t_old[3]-(-0.5*J_max*t_old[3]*t_old[3]+A_t_init*t_old[3]);
        V_t =  -0.5*J_max*t*t+A_t_init*t+V_t_init;

        // -J_max* t_old[3]* t_old[3]* t_old[3]/6+0.5*A_t_init* t_old[3]* t_old[3]+V_t_init* t_old[3]+S_t_init=S_t_old[3]
        S_t_init=S_t_old[3]-(-J_max* t_old[3]* t_old[3]* t_old[3]/6+0.5*A_t_init*t_old[3]* t_old[3]+V_t_init* t_old[3]);
        S_t =  -J_max*t*t*t/6+0.5*A_t_init*t*t+V_t_init*t+S_t_init;

        S_t_old[4] = S_t;
        V_t_old[4] = V_t;
        A_t_old[4] = A_t;
        t_old[4] = t;

        V_t_Virtual = -0.5*J_max*(t+0.0002)*(t+0.0002)+A_t_init*(t+0.0002)+V_t_init;
        S_t_Virtual = -J_max*(t+0.0002)*(t+0.0002)*(t+0.0002)/6+0.5*A_t_init*(t+0.0002)*(t+0.0002)+V_t_init*(t+0.0002)+S_t_init;

        if( S_t_Virtual>97*S_max/108 || V_t_Virtual<2*V_t_old[3]/3)
        {
             Interval_state++;
        }
        break;
    case 5:
        //J_t = 0;
        A_t =  A_t_old[4];

       //A_t_old[4]*t_old[4]+V_t_init = V_t_old[4]
        V_t_init = V_t_old[4]-A_t_old[4]*t_old[4];
        V_t =  A_t_old[4]*t+V_t_init;

        //0.5*A_t_old[4]*t_old[4]*t_old[4]+t_old[4]*V_t_init+S_t_init=S_t_old[4]
        S_t_init=S_t_old[4]-(0.5*A_t_old[4]*t_old[4]*t_old[4]+t_old[4]*V_t_init);
        S_t = 0.5*A_t_old[4]*t*t+V_t_init*t+S_t_init;

        S_t_old[5] = S_t;
        V_t_old[5] = V_t;
        A_t_old[5] = A_t;
        t_old[5] = t;

        S_t_Virtual = 0.5*A_t_old[4]*(t+0.0002)*(t+0.0002)+V_t_init*(t+0.0002)+S_t_init;
        V_t_Virtual = A_t_old[4]*(t+0.0002)+V_t_init;

        if( S_t_Virtual>53*S_max/54 || V_t_Virtual<V_t_old[3]/3)
        {
             Interval_state++;
        }
        break;
    case 6:
        //J_t = J_max;
         //J_max*t_old[5]+A_t_init = A_t_old[5];
        A_t_init  = A_t_old[5]-J_max*t_old[5];
        A_t = J_max*t+A_t_init;

        //0.5*J_max*t_old[5]*t_old[5] +A_t_init*t_old[5] +V_t_init = V_t_old[5]
        V_t_init = V_t_old[5]-(0.5*J_max*t_old[5]*t_old[5] +A_t_init*t_old[5]);
        V_t = 0.5*J_max*t*t+A_t_init*t+V_t_init;

        //J_max*t_old[5]*t_old[5]*t_old[5]/6+0.5*A_t_init*t_old[5]*t_old[5]+t_old[5]*V_t_init+S_t_init = S_t_old[5];
        S_t_init = S_t_old[5]-(J_max*t_old[5]*t_old[5]*t_old[5]/6+0.5*A_t_init*t_old[5]*t_old[5]+t_old[5]*V_t_init);
        S_t = J_max*t*t*t/6+0.5*A_t_init*t*t+t*V_t_init+S_t_init;

        S_t_old[6] = S_t;
        V_t_old[6] = V_t;
        A_t_old[6] = A_t;
        t_old[6] = t;
        A_t_Virtual = J_max*(t+0.0002)+A_t_init;
        V_t_Virtual = 0.5*J_max*(t+0.0002)*(t+0.0002)+A_t_init*(t+0.0002)+V_t_init;
        S_t_Virtual = J_max*(t+0.0002)*(t+0.0002)*(t+0.0002)/6+0.5*A_t_init*(t+0.0002)*(t+0.0002)+(t+0.0002)*V_t_init+S_t_init;

        if( S_t_Virtual>S_max || V_t_Virtual<0){
             Interval_state++;
        }
        break;
    case 7:
    	 counter++;
    	 S_t = S_t_old[6]+counter*(S_max-S_t_old[6])/2500;
    	 if(counter==2500)
    	     Interval_state++;
    	 break;
    default:
    	break;
    }

    t=t+((float32) 1/Ploop_freqency);

    return ((uint32)(S_t));
}


uint32 Basic_T_curve_Deccmd(float32 Msdtime_ms,float32 S_dec,float32 V_init,uint32 tclr,uint32 Ploop_freqency)
{

	static float32 t = 0;
	static float32 S_t,S_t_init,S_t_old;
    static float32 V_t_init,V_dec;
    //static float32 A_t;

    V_dec = 102400*V_init;
    if(tclr == 0)
    {
    	t = 0;
    }

    t=t+((float32) 1/Ploop_freqency);

    if(t <= Msdtime_ms/1000)
    {
        //A_t = -V_dec/time_step;

        V_t_init = V_dec;
        //V_t = -t*V_dec/Dectime_ms +V_t_init;

        S_t_init =S_dec;
        S_t =-0.5*t*t*V_dec/Msdtime_ms+t*V_t_init+S_t_init;
        S_t_old = S_t;
    }
    else
    {
    	 S_t = S_t_old;
    }


	return ((uint32)(S_t));
}


uint32 Advanced_S_curve_Pulsecmd(uint32 distance)
{

	static uint32 total =5000;
    static float32 J_t_new,scale;
    static float32 A_t_new,A_t_old;
	static float32 V_t_new,V_t_old;
    static float32 S_t_new,S_t_old;

    static uint32 counter;
    scale = (float32)distance/31250/125004;

    if(counter<total/4)
    {
        J_t_new = scale;
    }else if(counter<3*total/4)
    {
        J_t_new = -scale;
    }else if(counter<total)
    {
        J_t_new = scale;
    }

    if(counter<total)
    {
        A_t_new = A_t_old + J_t_new;
        V_t_new = V_t_old + A_t_new + 0.5*J_t_new;
        S_t_new = S_t_old + V_t_new + 0.5*A_t_new + J_t_new/6;

        A_t_old = A_t_new;
        V_t_old = V_t_new;
        S_t_old = S_t_new;
        counter++;
    }else
    {
        S_t_new = distance;
    }

    return ((uint32)(S_t_new));
}


