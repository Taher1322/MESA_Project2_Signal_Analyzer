%fftarray
%generate samples
fs = 1000; % Sampling frequency (samples per second) 
dt = 0.00001; % seconds per sample 
StopTime = 1; % seconds 
t = (0:dt:0.01000)'; % seconds 
F = 1004; % Sine wave frequency (hertz) 
data = sin(2*pi*F*t);
csvwrite('waveform.txt',data)
plot(t,data)
