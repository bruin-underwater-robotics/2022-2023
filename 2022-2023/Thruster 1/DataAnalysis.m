clc; clear all; close all;

%% Constants
mechAdv = 2; %Mechanical advantage

%% Trial 1
Trial_1_Raw =  importdata('Thruster1_Trial1.csv').data;
[Trial1Power, Trial1Thrust] = C_V_Analyze(Trial_1_Raw, mechAdv);

figure(1);
scatter(Trial1Power, Trial1Thrust, 'red');
hold on;

%% Trial 2
Trial_2_Raw =  importdata('Thruster1_Trial2.csv').data;
[Trial2Power, Trial2Thrust] = C_V_Analyze(Trial_2_Raw, mechAdv);


scatter(Trial2Power, Trial2Thrust, 'blue');
hold on;

%% Trial 3
Trial_3_Raw =  importdata('Thruster1_Trial3.csv').data;
[Trial3Power, Trial3Thrust] = C_V_Analyze(Trial_3_Raw, mechAdv);


scatter(Trial3Power, Trial3Thrust, 'black');
hold on;

%% Trial 4
Trial_4_Raw =  importdata('Thruster1_Trial4.csv').data;
[Trial4Power, Trial4Thrust] = P_Analyze(Trial_4_Raw, mechAdv);


scatter(Trial4Power, Trial4Thrust, 'green');
hold on;

%% Trial 5
Trial_5_Raw =  importdata('Thruster1_Trial5.csv').data;
[Trial5Power, Trial5Thrust] = P_Analyze(Trial_5_Raw, mechAdv);


scatter(Trial5Power, Trial5Thrust, 'yellow');
hold on;


%% Plotting best fit
xmin = 0;
xmax = 60;
num = 1000;
xFit = linspace(xmin, xmax, num);

%Trial 1 best fit
coefficients1 = polyfit(Trial1Power, Trial1Thrust, 1);
yFit1 = polyval(coefficients1, xFit);
plot(xFit, yFit1, 'red');

%Trial 2 best fit
coefficients2 = polyfit(Trial2Power, Trial2Thrust, 1);
yFit2 = polyval(coefficients2, xFit);
plot(xFit, yFit2, 'blue');

%Trial 3 best fit
coefficients3 = polyfit(Trial3Power, Trial3Thrust, 1);
yFit3 = polyval(coefficients3, xFit);
plot(xFit, yFit3, 'black');

%Trial 4 best fit
coefficients4 = polyfit(Trial4Power, Trial4Thrust, 1);
yFit4 = polyval(coefficients4, xFit);
plot(xFit, yFit4, 'green');

%Trial 5 best fit
coefficients5 = polyfit(Trial5Power, Trial5Thrust, 1);
yFit5 = polyval(coefficients5, xFit);
plot(xFit, yFit5, 'yellow');

%% Making the graph look nice
xlabel('Power (W)');
ylabel('Force (gf)');
legend('', '', '', '', '','Trial 1', 'Trial 2', 'Trial 3', 'Trial 4', 'Trial 5', '', '', '', '', '');
disp(coefficients1)
disp(coefficients2)
disp(coefficients3)
disp(coefficients4)
disp(coefficients5)
