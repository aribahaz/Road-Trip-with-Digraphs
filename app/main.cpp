// main.cpp
//
// ICS 46 Spring 2018
// Project #5: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include <iostream>
#include <iomanip>
#include <vector>
#include "TripReader.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"

double DistFunc (const RoadSegment& rs) 
{
  return rs.miles;
}
  
double TimeFunc (const RoadSegment& rs)
{
  return rs.miles/rs.milesPerHour;
}

void formatIt(double t)
{
  double temp = t*3600;
  int hrs = temp/3600;
  int mins = (temp - 3600*hrs) / 60;
  double secs = temp - hrs*3600 - mins*60;
  
  if(hrs)
    {
      std::cout << hrs << " hours " << mins << " mins "; 
    }
  else if(mins)
    {
      std::cout << mins << " mins ";
    }
  std::cout << secs;
}

std::vector<int> coord(std::map<int, int> pv, Trip tp)
{
  int x = tp.startVertex;
  int y = tp.endVertex;
  std::vector<int> num;
  while(x != y)
    {
      num.emplace(num.begin(), y);
      y = pv[y];
    }
  num.emplace(num.begin(), x);
  return num;
}

void calcdist(int i, std::vector<int> num, double& tot, RoadMap rm)
{
  RoadSegment rs = rm.edgeInfo(num[i-1], num[i]);
  tot += rs.miles;
  std::cout << std::fixed << "  Continue to " << rm.vertexInfo(num[i])
            << " (" << std::setprecision(1) << rs.miles << " miles)\n";
}

void distance(std::map<int, int> pv, Trip tp, RoadMap rm)
{
  std::vector<int> num = coord(pv, tp);
  double tot = 0;
  for(int i = 1; i < num.size(); ++i)
     {
       calcdist(i, num, tot, rm);
     }
  std::cout << "Total distance: " << tot << " miles\n\n";
}

double calctime(int i, std::vector<int> num, double& tot, RoadMap rm)
{
  double pathtime = 0;
  RoadSegment rs = rm.edgeInfo(num[i-1], num[i]);
  tot += rs.miles/rs.milesPerHour;
  pathtime += rs.miles/rs.milesPerHour;
  std::cout << std::fixed << "  Continue to " << rm.vertexInfo(num[i])
            << " (" << std::setprecision(1) << rs.miles << " @ "
            << rs.milesPerHour << "mph = ";
  return pathtime;
}

void time(std::map<int, int> pv, Trip tp, RoadMap rm)
{
  std::vector<int> num = coord(pv, tp);
  double tot = 0;
  for(int i = 1; i < num.size(); ++i)
     {
       double pv = calctime(i, num, tot, rm);
       formatIt(pv);
       std::cout << " secs)\n";
     }
  std::cout << "Total time: ";
  formatIt(tot);
  std::cout << " secs\n\n";
}

int main()
{
  InputReader inp = InputReader(std::cin);
  RoadMapReader rmdrk;
  RoadMap rm = rmdrk.readRoadMap(inp);
  TripReader tp;
  std::vector<Trip> tpvec = tp.readTrips(inp);
  std::map<int, int> dijk;
  struct v
  {
    std::string strt;
    std::string end;
  };
  
  for(auto& ent: tpvec)
    {
      if(ent.metric == TripMetric::Distance)
        {
          v d;
          d.strt = rm.vertexInfo(ent.startVertex);
          d.end = rm.vertexInfo(ent.endVertex);
          std::cout << "Shortest distance from " << d.strt << " to " << d.end
                    << std::endl << "  Begin at " << d.strt << std::endl;
          dijk = rm.findShortestPaths(ent.startVertex, DistFunc);
          distance(dijk, ent, rm);
        }
      else
        {
           v t;
           t.strt = rm.vertexInfo(ent.startVertex);
           t.end = rm.vertexInfo(ent.endVertex);  
           std::cout << "Shortest time from " << t.strt << " to " << t.end
                     << std::endl << "  Begin at " << t.strt << std::endl;
          dijk = rm.findShortestPaths(ent.startVertex, TimeFunc);
          time(dijk, ent, rm);
        }
    }

  return 0;
}

