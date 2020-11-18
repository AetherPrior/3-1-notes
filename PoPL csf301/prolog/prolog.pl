speed(ford,100).
speed(dodge,100).
speed(chevy, 200).
tim(ford,10).
dist(X,Y) :- speed(X,Speed),tim(X,Time),Y is Speed * Time.
dist(ford,1000).
