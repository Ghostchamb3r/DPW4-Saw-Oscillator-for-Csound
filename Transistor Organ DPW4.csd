<CsoundSynthesizer>
<CsOptions>
-odac --opcode-lib=newopc.dylib
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 64
nchnls = 1
0dbfs = 1


instr 1
icps cpsmidi
iamp ampmidi 1
a16 newopc icps*0.5, iamp
a8 newopc icps, iamp
a4 newopc icps*2, iamp
a2 newopc icps*4, iamp
a1 newopc icps*8, iamp
aenv linenr a16+a8+a4+a2+a1,0.01,0.1,0.01
out aenv*0.1
endin

</CsInstruments>
<CsScore>

</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="background">
  <r>240</r>
  <g>240</g>
  <b>240</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
