#include "csdl.h"

//Vesa Valimaki, Juhan Nam, Julius O. Smith and Jonathan S. Abel
//Alias-Suppressed Oscillators Based on Differentiated Polynomial Waveforms
//IEEE Transactions on Audio, Speech, and Language Processing 18(4) May 2010, pp 786--798
// Original SuperCollider implementation at:
// https://github.com/supercollider/sc3-plugins/blob/main/source/AntiAliasingOscillators/AntiAliasingOscillators.cpp
// Under DPW4Saw functions
/*
To Compile:

This is the correct command lol
gcc -O2 -dynamiclib -o newopc.dylib DPW4SawC.c -DUSE_DOUBLE -I/Library/Frameworks/CsoundLib64.framework/Versions/6.0/Headers -arch x86_64

*/
/*
DATA STRUCTURE 
************************************/
typedef struct _newopc {
OPDS h;
MYFLT *out;
MYFLT *in1, *in2;
MYFLT freq;
MYFLT amp;
double differentiations[3];
double differentiations2[2];
double phase;
} newopc;

/*
INITIALIZATION
************************************/
int new_opc_init(CSOUND *csound, newopc *p){
        
    p->phase = 0.0;
    for(int i =0; i < 3;++i){
        p->differentiations[i]=0.0;
    }
     for(int i =0; i < 2;++i){
        p->differentiations2[i]=0.0;
    }
    return OK;
}

/*
PROCESSING
************************************/

int new_opc_process_audio(CSOUND *csound, newopc *p){
  
    MYFLT *aout = p->out;  /* output signal */
    MYFLT sar = csound->GetSr(csound);
    MYFLT freq = *p->in1;
    MYFLT amp= *p->in2;
    double phasestep = freq/sar;
	double period = 1.0/phasestep;
    double phase = p->phase;
    double diff1 = p->differentiations[0];
	double diff2 = p->differentiations[1];
	double diff3 = p->differentiations[2];
    // for DPW2
    double diff4 = p->differentiations2[0];
    double diff5 = p->differentiations2[1];
double ampcompensation = 0.0052083333333333*period*period*period;
double ampcompensation2 = 0.25*period;
int inNumSamples = CS_KSMPS;
int d;
double ampitup = 1.0;
double ampitup2 = 1.0;
/*
if(freq > 600.0){
    for (d = 0; d < inNumSamples; ++d) { 

        phase += phasestep; 
        if (phase > 1) 
        {phase -= 1.0;} 

        double temp = 2.0 * phase - 1.0;
        temp = temp*temp;
        temp = temp*temp - (2.0*temp);

        double temp2 = temp;
			temp = temp2 - diff1;
			diff1 = temp2;

			temp2 = temp;
			temp = temp2 - diff2;
			diff2= temp2;

			temp2 = temp;
			temp = temp2 - diff3;
			diff3= temp2;

    

            aout[d] = temp;
    }
}
else if(freq > 400.0){
*/

    double g;
    double oneminusg;

    if(freq > 600.0){
        g = 1.0;
        oneminusg = 0.0;
    }
    else if(freq > 400.0){
        g = (freq - 400.0) * 0.005;
        g *= g;
        oneminusg = 1.0 - g;
    }
    else{
        g = 0.0;
        oneminusg = 1.0;
    }
    
    for(d=0; d < inNumSamples; ++d){
        phase += phasestep;
        if(phase>1.0){phase -= 1.0;}
        double temp = 2.0 * phase - 1.0;
        temp = temp*temp;
        double dpw2 = diff5;

        double temp2 = temp;
        diff5 = temp2 - diff4;
        diff4 = temp2;

        // ampcompensation
        diff5*= ampcompensation2;


        temp = temp*temp - (2.0 * temp);

        // this might need to go to output here
        // but we'll differentiate 3 more times like Vesa does

        temp2 = temp;
			temp = temp2 - diff1;
			diff1 = temp2;

			temp2 = temp;
			temp = temp2 - diff2;
			diff2= temp2;

			temp2 = temp;
			temp = temp2 - diff3;
			diff3= temp2;

           temp *= ampcompensation;
           aout[d]= (g*temp) + (oneminusg*dpw2);
           /*
           if(freq < 400){
            aout[d]= temp + dpw2 *7.0;
           }
           else{
           aout[d]= temp + dpw2;
           }
           */
    }
//}
/*
    else{ 
		for (int d=0; d < inNumSamples; ++d) {

			phase += phasestep;
			if (phase > 1.0) phase -= 1.0;

			double temp= 2.0*phase- 1.0;

			temp = temp*temp;

			//now one differentiation to return it to linear from x^2
			double temp2 = temp;
			temp = temp2 - diff4;
			diff4 = temp2;

			//output[i]= 0.0052083333333333f*temp; //ampcompensation*temp;
			aout[d]= diff5;
			//delay of one sample required
			diff5= temp;
			//output[i]= temp;
		}
    }
    */

            p->differentiations[0] = diff1;
	        p->differentiations[1] = diff2;
	        p->differentiations[2] = diff3;
            p->differentiations2[0] = diff4;
            p->differentiations2[1] = diff5;

    


p->phase = phase;
// test to ensure internal freq var matches MIDI input
csound->Message(csound, "frequency: %f Hz\n", freq);
    return OK;

}

/*
REGISTRATION
*************************************/

static OENTRY localops[] = {
    {"newopc", sizeof(newopc), 0, 7, "a", "ii",
     (SUBR) new_opc_init, (SUBR) new_opc_process_audio,}
};

LINKAGE