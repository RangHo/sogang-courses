function mattlabbhw()
width = 10; % 다리의 폭, 6m가 넘어가면 죽기 때문에 사실 의미는 없는 수치이다.
length = 100; % 다리의 길이.

iterations = 100000; % 시행 횟수.

XList = []; % 시행할동안 X의 값을 저장할 리스트.
TimeSurvival = 0; % 50초 이상 생존한 사람의 수.
ClearTotal = 0; % 전체 다리를 건넌 사람의 수.

FFS_People_Needed = 0; % 456명 다리길이 계산을 위해 사용할 필요사람의 수
FFS_ClearTotal = 0; % 456명 다리길이 계산을 위해 사용하는 다리를 건넌 사람의 수
FFS_Clear_Rate = 0; % 456명 다리길이 계산을 위해 사용하는 성공확률
FFS_XList = []; % 456명 다리길이 계산을 위해 사용하는 X의 값을 저장하는 리스트
NewLength = 100; % 456명중 3명이 통과하기 위해 필요한 다리의 길이


%========== 실험적으로 평균, 표준편차, 히스토그램 구하기 ==========%

i = 0; % Counter

    while i < iterations % 다리건너기를 iterations만큼 시행.
       
        [Clear, X] = OneMann(length); % 한사람이 다리를 건넘.
        XList(end + 1) = X; % 다리 건넌 결과를 XList에 append.
    
        if X > 50 % 50초 이상 살아남았으면 1 추가.
            TimeSurvival = TimeSurvival + 1;
        end
    
        ClearTotal = ClearTotal + Clear; 
        i = i + 1;
    end

AVG_X = mean(XList) % X의 평균값.
STD_X = std(XList) % X의 표준편차.
Clear_Rate = ClearTotal / iterations;
Halfway_Survival_Rate = TimeSurvival / iterations;
People_Needed = 3/Clear_Rate % 평균적으로 3명이 건너는데 필요한 사람의 수.
Halfway_Survival_Rate = Halfway_Survival_Rate * 100 % 50초후 생존확률(%)

fig1 = figure(1); % 히스토그램 그리기
h = histogram(XList);
xlabel('Walk Distance (X)')
ylabel('No. Of People')
title('SquidGame Histogram')
%title('It''s Just Like SquidGame Bro!')
set(gca, 'FontSize', 10)


%========== 평균 70명인가 나오는거 시각화 ==========%

i = 0;
fig2 = figure(2);
ax2 = axes('Parent', fig2);  
hold on
    while i < People_Needed % 시각화하기 위한 루프.
    % 인간적으로 100000번 루프한거를 다 시각화하기에는 좀 힘들어서 조금만 함.
    % 그래도 이렇게 겹치니까 잘 안보임...
        [CurrentPosPlot,X] = OneMannGraph(length);
         h = plot(ax2,CurrentPosPlot);

        i = i + 1;
    end
    
title('Random Walk Visualization, I Guess...?')
xlabel('Walk Distance (X)')
ylabel('Left / Right Position')
set(gca, 'FontSize', 10)
hold off


%========== 평균 456명을 위한 다리길이 구하기(오래걸림) ==========%

FFS_People_Needed = People_Needed;

while FFS_People_Needed < 456 % 3명이 건너는데 456명이 필요할 다리의 길이를 구함.
    i = 0;
    FFS_XList = [];
    FFS_ClearTotal = 0;
    NewLength = NewLength + 10; % 10메터씩 증가.
     while i < iterations % 다리건너기를 iterations만큼 시행.
       
            [Clear, X] = OneMann(NewLength); % 한사람이 다리를 건넘.
            FFS_XList(end + 1) = X; % 다리 건넌 결과를 FFS_XList에 append
    
            FFS_ClearTotal = FFS_ClearTotal + Clear; 
            i = i + 1;
     end
    FFS_Clear_Rate = FFS_ClearTotal / iterations;
    FFS_People_Needed = 3/FFS_Clear_Rate; %3명이 건너는데 필요한 사람수 계산.
end

Text = ['456명중 평균적으로 3명이 통과하기 위한 새로운 다리 길이:',num2str(NewLength),'m'];
disp(Text)
NewLength; % 456명중 평균적으로 3명이 건너는 결과를 갖는 다리 길이.

end

%==========나머지 함수==========%

function [Clear, X] = OneMann(Length) % 한 사람이 다리를 건넘.
    X = 0; % X
    Clear = 0; % 통과여부

    CurrentPos = 0; % 현위치 (1초에 1미터 나감으로 시간과도 동일.)

    while((CurrentPos > -6)&&(CurrentPos < 6)) %6미터 이내
    
        random = rand(1,1); %0~1 사이의 무작위 숫자 생성
        if random < 0.5 % 0.5 이하일때 오른쪽
            direction = 1;
        else % 0.5 이상일때 왼쪽
            direction = -1;
        end
   
        CurrentPos = CurrentPos + direction;
        X = X+1;
   
        if X >= Length % 통과조건
            Clear = 1;
            break
        end 
    end
end


function [CurrentPosPlot,X] = OneMannGraph(Length) % 다리 건너는거를 시각화

    CurrentPosPlot = [];

    X = 0; % X

    CurrentPos = 0; % 현위치 (1초에 1미터 나감으로 시간과도 동일.)

    while((CurrentPos > -6)&&(CurrentPos < 6)) %6미터 이내
    
        random = rand(1,1); %0~1 사이의 무작위 숫자 생성
        if random < 0.5 % 0.5 이하일때 오른쪽
            direction = 1;
        else % 0.5 이상일때 왼쪽
            direction = -1;
        end
   
        CurrentPos = CurrentPos + direction;
        CurrentPosPlot(end + 1) = CurrentPos;
        
        X = X+1;
       
        
        if X >= Length
            break
        end 
    end

end
