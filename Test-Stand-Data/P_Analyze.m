%Analyze data given power, force

function [power, thrust] = P_Analyze(dataRaw, mechAdv)
col = 2;
row = length(dataRaw)/col;
reshapedDataRaw = reshape(dataRaw, row, col);
power = reshapedDataRaw(:,1); %power, W
thrustRaw = reshapedDataRaw(:,2); %Thrust, gf

offset = thrustRaw(1); %Thrust offset, gf
thrust = (thrustRaw-offset)*mechAdv; %Actual thrust produced by motor, gf

end