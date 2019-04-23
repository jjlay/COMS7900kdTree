% Concerns:
% 1) for non 2^n data, check for dataL/dataR are empty
% 2) pass structs by reference so they get changed at all levels
% 
% 
% 
% 

%%%%%%%%%%%%
%%% main %%%
%%%%%%%%%%%%
nPts = 10;

% generate data
data = rand( nPts, 2 );

tree = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{}, 'n',{}, 'd', {}, 'c',{} );
tree(1).x1 = 0;
tree(1).x2 = 1;
tree(1).y1 = 0;
tree(1).y2 = 1;
tree = buildTree( data, tree );
disp("Tree complete!!!")

data

center = [ 0.5, 0.5 ];
rad    = 0.25;
found  = searchTree( tree, center, rad )




% plot data
figure('Renderer', 'painters', 'Position', [600 10 650 650])
hold on
plot( data(:,1), data(:,2), 'b.', 'MarkerSize', 12 )
plot( data(:,1), data(:,2), 'bo', 'MarkerSize', 8 )
% plotTree( tree )
circle( center(1), center(2), rad)
axis( [ 0, 1, 0, 1 ] )
hold off
%%%%%%%%%%%%
%%% done %%%
%%%%%%%%%%%%

function [ found ] = searchTree( tree, c0, rad )
    
    % check left
    xlen  = tree(1).x2 - tree(1).x1;
    ylen  = tree(1).y2 - tree(1).y1;
    
    check = ( abs( tree(1).c(1) - c0(1) ) <= abs( rad + xlen/2 ) ) && ... 
            ( abs( tree(1).c(2) - c0(2) ) <= abs( rad + ylen/2 ) );
    
    found = [];
    if check == 1
        L = [];
        R = [];
        if tree(1).n > 1
            L = searchTree( tree(1).l, c0, rad );
            R = searchTree( tree(1).r, c0, rad );
            found = [ L; R ];
        else
            found = tree(1).d;
        end
    end
    tree(1).n
    found
    
end

function plotTree( tree )
    
    if tree(1).n > 1
        if tree(1).i == 1
            plot( [ tree(1).v, tree(1).v ], [ tree(1).y1, tree(1).y2 ], 'r', 'LineWidth', 2 )
        else
            plot( [ tree(1).x1, tree(1).x2 ], [ tree(1).v, tree(1).v ], 'r', 'LineWidth', 2 )
        end
        
        plotTree( tree(1).l )
        plotTree( tree(1).r )
    end
    
end

function tree = buildTree( data, tree )
    
    % pause(0.1)
    
    % get length
    [ nPts, nDim ] = size( data );
    tree(1).n = nPts;
    tree(1).c = [ 0.5*( min(data(:,1)) + max(data(:,1)) ), 0.5*( min(data(:,2)) + max(data(:,2)) )];
    
    if nPts > 1
        disp("Creating branch...")
        
        % get range and sortInd
        xmin = min( data(:,1) );
        xmax = max( data(:,1) );
        ymin = min( data(:,2) );
        ymax = max( data(:,2) );
    
        xlen = xmax - xmin;
        ylen = ymax - ymin;
        
        tree(1).x1 = xmin;
        tree(1).x2 = xmax;
        tree(1).y1 = ymin;
        tree(1).y2 = ymax;
        
        if xlen > ylen
            sortInd = 1;
        else
            sortInd = 2;
        end
        
        % sort
        [tmp, ind] = sort( data(:,sortInd) );
        dataSort   = zeros( nPts, 2 );
        if sortInd == 1
            dataSort(:,1) = tmp;
            dataSort(:,2) = data(ind,2);
        else
            dataSort(:,1) = data(ind,1);
            dataSort(:,2) = tmp;
        end
        
        half = cast( floor(nPts/2), 'uint16' );
        
        tree(1).i = sortInd;
        tree(1).v = 0.5*( dataSort(half,sortInd) + dataSort(half+1,sortInd) );
        
        % split
        dataLeft  = dataSort(1:half,:);
        dataRight = dataSort(half+1:end,:);
        
        % call buildTree
        treeLeft  = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{} );
        treeRight = struct( 'p',{}, 'l',{}, 'r',{}, 'i',{}, 'v',{}, 'x1',{}, 'x2',{}, 'y1',{}, 'y2',{} );
        
%         if sortInd == 1
%             treeLeft(1).x1 = tree(1).x1;
%             treeLeft(1).x2 = tree(1).v;
%             treeLeft(1).y1 = tree(1).y1;
%             treeLeft(1).y2 = tree(1).y2;
%             
%             treeRight(1).x1 = tree(1).v;
%             treeRight(1).x2 = tree(1).x2;
%             treeRight(1).y1 = tree(1).y1;
%             treeRight(1).y2 = tree(1).y2;
%         else
%             treeLeft(1).x1 = tree(1).x1;
%             treeLeft(1).x2 = tree(1).x2;
%             treeLeft(1).y1 = tree(1).y1;
%             treeLeft(1).y2 = tree(1).v;
%             
%             treeRight(1).x1 = tree(1).x1;
%             treeRight(1).x2 = tree(1).x2;
%             treeRight(1).y1 = tree(1).v;
%             treeRight(1).y2 = tree(1).y2;
%         end
        
        if ~isempty(dataLeft)
            treeLeft = buildTree( dataLeft, treeLeft );
        end
        if ~isempty(dataLeft)
            treeRight = buildTree( dataRight, treeRight );
        end
        
        treeLeft(1).p = tree;
        treeLeft(1).p = tree;
                
        tree(1).l = treeLeft;
        tree(1).r = treeRight;
    else
        tree(1).d  = data;
        tree(1).c  = data;
        tree(1).x1 = data(1);
        tree(1).x2 = data(1);
        tree(1).y1 = data(2);
        tree(1).y2 = data(2);
        disp("Branch complete")
    end
    
end

function circle(x,y,r)
th = 0:pi/50:2*pi;
xunit = r * cos(th) + x;
yunit = r * sin(th) + y;
plot(xunit, yunit, 'r');
end
