%Cut off frequency of 6
%Sample rate of 62.5kHz and a length of 25 time differences, if we
%meaning that the new sample rate is now 2.5kHz, or every 25 samples we
%take in we spit out one value in y, with x multiplied by the coefficients
%in h

%second argument is the noramlized cutoff frequency, between 0 to the
%Nyquist criterion, A 6kHz cutoff with a nyquist frequency of 24 kHz has a
%24 kHz (48/2) has a noramlized frequency of 6/24, in this case a Nyquist
%frequency of 62.5/2 has a noramlized frequency of 6/(62.2/), (6 is the cut
%off frequency)

h = fir1(24, (6*2)/62.5);
h = fliplr(h);

plot(h)
