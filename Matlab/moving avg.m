
clear

load('C:\Users\user\Desktop\hy-kist\OpenBCI\AAD\Matlab\all_acc.mat')
%% moving avg - overall
% all acc
mean_acc = mean(accuracy,2);
% moving average
mov_1 = movmean(accuracy, 1);
mov_3 = movmean(accuracy, 3);
mov_5 = movmean(accuracy, 5);
mov_7 = movmean(accuracy, 7);

mean_mov_1 = mean(mov_1,2);
mean_mov_3 = mean(mov_3,2);
mean_mov_5 = mean(mov_5,2);
mean_mov_7 = mean(mov_7,2);

% sum
com = [mean_acc, mean_mov_1, mean_mov_3, mean_mov_5, mean_mov_7];
% sub by var

% mean each
all = mean(com,1);

s = std(com*100);

%% fixed & switching

fix = accuracy(:,1:12);
swi = accuracy(:,13:end);


% moving average-fix
mov_1 = movmean(fix, 1);
mov_3 = movmean(fix, 3);
mov_5 = movmean(fix, 5);
mov_7 = movmean(fix, 7);

mean_mov_1 = mean(mov_1,2);
mean_mov_3 = mean(mov_3,2);
mean_mov_5 = mean(mov_5,2);
mean_mov_7 = mean(mov_7,2);

com_fix = [mean(fix,2), mean_mov_1, mean_mov_3, mean_mov_5, mean_mov_7];

mean_fix = mean(com_fix,1);
s_fix = std(com_fix*100);

% moving average-swi
mov_1 = movmean(swi, 1);
mov_3 = movmean(swi, 3);
mov_5 = movmean(swi, 5);
mov_7 = movmean(swi, 7);

mean_mov_1 = mean(mov_1,2);
mean_mov_3 = mean(mov_3,2);
mean_mov_5 = mean(mov_5,2);
mean_mov_7 = mean(mov_7,2);

com_swi = [mean(swi,2), mean_mov_1, mean_mov_3, mean_mov_5, mean_mov_7];

mean_swi = mean(com_swi,1);
s_swi = std(com_swi*100);

%% optimal lambda check
clear
load('C:\Users\LeeJiWon\Desktop\OpenBCI\save_data\Accuracy_onlambda.mat');

lambda = 10.^(-6:1:5);

mean_acc = mean(Acc(:,15:end),2);

[max_acc,idx] = max(mean_acc);
op_lam = lambda(idx);

max_fix =  mean(Acc(idx,15:26),2);
max_swi =  mean(Acc(idx,27:end),2);

s = std(Acc(idx,15:end)*100);
s_fix = std(Acc(idx,15:26)*100);
s_swi = std(Acc(idx,27:end)*100);