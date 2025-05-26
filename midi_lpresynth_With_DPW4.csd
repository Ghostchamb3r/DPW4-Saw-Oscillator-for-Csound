<CsoundSynthesizer>
<CsOptions>
-odac --opcode-lib=newopc.dylib
</CsOptions>
<CsInstruments>
0dbfs = 1
nchnls = 1
instr 1
  icps cpsmidi  
  kcf_max = 8*icps	// MAX CF 8 times the fundamental
  kcf_min = 2*icps	// MIN CF 2 times the fundamental
  kspac =  icps*0.5	// spacing between filters 
  ires = 0.8			// amount of resonance
  kenv1	madsr 0.1, 0.01, 0.8, 0.1
  iamp ampmidi 1
  kenv2  	madsr 0.1,0.1, 0.7, 0.1
  kcf 	= kenv2*(kcf_max - kcf_min) + kcf_min
  a1 	newopc  icps, iamp  	; DWP4 Sawtooth
  aenv linenr a1,0.01,0.4,0.01

 a21 	moogvcf   a1*0.3, kcf-kspac, ires
 a22 	moogvcf   a1*0.3, kcf+kspac, ires   
       	outs          a21,a22
endin

</CsInstruments>
<CsScore>

</CsScore>
</CsoundSynthesizer>


<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>0</x>
 <y>0</y>
 <width>0</width>
 <height>0</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
