#ifndef DEBUGSERIALPORT_H
#define DEBUGSERIALPORT_H

#define DEBUG
//comment to pass in non debug mode


#define DEBUGPORT Serial
#define DEBUGSPEED 115200

#define sp(X) DEBUGPORT.print(X)
#define spl(X) DEBUGPORT.println(X)

#ifdef DEBUG
#define DSP(X) sp(X)
#define DSPL(X) spl(X)
#define DSPF(X) sp(F(X))
#define DSPLF(X) spl(F(X))
#else
#define DSP(X)
#define DSPL(X)
#define DSPF(X)
#define DSPLF(X) 
#endif

#ifdef DEBUG
#define DEFDPROMPT(X) String dPrompt = F("<Volab "); \
    dPrompt += X; dPrompt += F(" : >");
#else
#define DEFDPROMPT(X) String dPrompt = "";
#endif    

#endif

