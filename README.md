# DPW4-Saw-Oscillator-for-Csound
An implementation of the DWP4 (Differentiated Parabolic Waveform) Sawtooth oscillator for Csound. 

The DPW4 Saw opcode is an a-rate opcode that takes two i-rate arguments for frequency, and amplitude, in that order.
It will require adding --opcode-lib=newopc.dylib in the options tag next to -odac of the CSD file.

To install it find your plugins folder for Csound and move the dylib file to it. 
On Mac this might be somewhere such as: 
/Library/Frameworks/CsoundLib64.framework/Versions/6.0/Resources/Opcodes64

Once the dylib file is installed the opcode should be ready to use.

The DPW4 Saw algorithm is an anti-aliasing oscillator algorithm developed by Vesa Välimäki in the 
Following papers:
Välimäki, V., 2005. Discrete-Time Synthesis of the Sawtooth Waveform With Reduced Aliasing. IEEE SIGNAL Process. Lett. 12.

Vesa Valimaki, Juhan Nam, Julius O. Smith and Jonathan S. Abel
Alias-Suppressed Oscillators Based on Differentiated Polynomial Waveforms
IEEE Transactions on Audio, Speech, and Language Processing 18(4) May 2010, pp 786--798

DPW4Saw was originally implemented in SuperCollider as part of a suite of anti-aliasing oscillator Ugens. The DPW4 Opcode was derived from this source code available at:

https://github.com/supercollider/sc3-plugins/blob/main/source/AntiAliasingOscillators/AntiAliasingOscillators.cpp

The DPW4 Saw differentiates the integral of the sawtooth waveform to produce a sawtooth waveform with reduced aliasing in comparison to the trivial sawtooth waveform. Amp compensation and level of differentiation varies depending on the frequency bandwidth, to accommodate the spectral tilt that differentiation has on the waveform in lower frequencies. The result is a reduction on aliasing with a minimal degree of computational perplexity. 
