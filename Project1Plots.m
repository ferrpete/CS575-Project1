% Project1Plot.m
% Peter Ferrero, Oregon State University, 4/15/2018, CS575, Project 1
% A file to produce the plots for Project 1 of CS575

load('TrapezoidalRuleData.txt')

threads = unique(TrapezoidalRuleData(:,1));
numNodes = unique(TrapezoidalRuleData(:,2));
peakPerformance = TrapezoidalRuleData(:,3);
averagePerformance = TrapezoidalRuleData(:,4);

peakPerformance = reshape(peakPerformance,length(numNodes),[]);

threadLegend = [];

for i=1:length(threads)
    
    threadLegend = [threadLegend, strcat(string(threads(i)), " Thread")];
    
end

nodeLegend = [];

for i=1:length(numNodes)
    
    nodeLegend = [nodeLegend, strcat(string(numNodes(i)), " Nodes")];
    
end

figure
plot(numNodes,peakPerformance)
xlabel('Number of Nodes')
ylabel('Peak Performance, MegaHeights/Sec')
legend(threadLegend,'Location','NorthEastOutside')
axis([0,inf,0,120])

figure
plot(threads,peakPerformance')
xlabel('Number of Threads')
ylabel('Peak Performance, MegaHeights/Sec')
legend(nodeLegend,'Location','NorthEastOutside')