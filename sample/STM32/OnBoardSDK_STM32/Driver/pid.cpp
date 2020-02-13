#include "pid.h"
#include "main.h"


fp32 Position_Type_PID(Pid_error *sptr, Pid_parameter *PID, fp32 NowData, fp32 Point)
{
		fp32 error , final_output; 
		
		error = Point - NowData;    
		
	  LimitMax(error , PID->err_limit);

		sptr->SumError += PID->i * error;
		
	  LimitMax(sptr->SumError , PID->i_limit);
	  	
		final_output = PID->p * error + sptr->SumError + PID->d * (error  - sptr->LastError);
		
		sptr->LastError = error;  
		
	  if (PID->output_limit != 0)	    
		    LimitMax(final_output , PID->output_limit);	  
	
		return final_output;      	
}



