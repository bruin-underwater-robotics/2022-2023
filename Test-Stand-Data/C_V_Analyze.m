%Analyze data given current, voltage, force

function [power, thrust] = C_V_Analyze(dataRaw, mechAdv)
col = 3;
row = length(dataRaw)/col;
reshapedDataRaw = reshape(dataRaw, row, col);
volt = reshapedDataRaw(:,1); %current, A
curr = reshapedDataRaw(:,2); %voltage, V
thrustRaw = reshapedDataRaw(:,3); %Thrust, gf

power = curr.*volt; %Power, W

offset = thrustRaw(1); %Thrust offset, gf
thrust = (thrustRaw-offset)*mechAdv; %Actual thrust produced by motor, gf

end
