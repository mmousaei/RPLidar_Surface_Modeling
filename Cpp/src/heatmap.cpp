/*    heatmap.cpp - class source for heatmap image generation from
 *                    RPLidar surface model using gnuplot
 *
 *    Carnegie Mellon University
 *    Authors: Mohammadreza Mousei
 *    Contact: mmousaei@andrew.cmu.edu
 *
 */
 #include "heatmap.h"

 std::vector<std::vector<std::pair<double, double>>> *heatmapVector;
 std::vector< std::pair < int, int > > sections_ind;
std::vector<std::vector<double>> HeatMap::original_request_csv;
  Error HeatMap::generateHeatMaps(std::string fname, std::vector<std::vector<std::pair<double, double>>> *polarHeatmap)
  {
    heatmapVector = polarHeatmap;
    err = csv.read(fname, &original_request_csv);

    int max_plot_id = 0;
    for(int i = 0; i < original_request_csv[0].size(); i++)
    {
      if(original_request_csv[1][i] > max_plot_id)
      {
        max_plot_id = original_request_csv[1][i];
      }
    }

    std::cout << "heatmap size: " << heatmapVector->size() << " csv size: " << original_request_csv[0].size() << '\n';

    int begin_ind, end_ind, begin_end_ind = 0, plot_ind, last_plot_ind;


    for(int i = 1; i < original_request_csv[0].size(); i++)
    {
      plot_ind = original_request_csv[1][i];
      if(begin_end_ind == 1)
      {
        if(plot_ind != last_plot_ind && plot_ind != 0)
        {
          end_ind = i - 1;
          generateHeatMapSection(last_plot_ind, original_request_csv[3][i - 1], begin_ind, end_ind);
          begin_end_ind = 0;
          std::cout << "i = " << i << " , plot_ind = " << last_plot_ind << " , start = " << begin_ind << " , end = " << end_ind << '\n';
        }
        if(last_plot_ind != 0 && plot_ind == 0)
        {
          begin_end_ind = 0;
          end_ind = i - 1;
          std::cout << "i = " << i << " , plot_ind = " << last_plot_ind << " , start = " << begin_ind << " , end = " << end_ind << '\n';
          generateHeatMapSection(last_plot_ind, original_request_csv[3][i - 1], begin_ind, end_ind);
        }
      }
      if(begin_end_ind == 0)
      {
        if(plot_ind != last_plot_ind && plot_ind != 0)
        {
          begin_ind = i;
          begin_end_ind = 1;
        }
      }
      last_plot_ind = plot_ind;
    }

  }

  Error HeatMap::generateHeatMapSection(int section, bool forward_reverse, int begin, int end)
  {
    int frame[5000][359];

    // float *frame = new float[ysize][xsize];
    double radius = 0.37;
    int min_frame = 0;
    memset(frame,0,sizeof(frame));

    if(!forward_reverse)
    {
      for(int i = 0 ; i < heatmapVector->size(); i++)
      {
        for(int j = 0; j < heatmapVector->at(0).size(); j++)
        {
          if(!std::isinf(heatmapVector->at(i)[j].first) && !std::isinf(heatmapVector->at(i)[j].second) && heatmapVector->at(i)[j].first < 1 && heatmapVector->at(i)[j].first > -1)
          {
            frame[i][j] = radius*1000 - heatmapVector->at(i)[j].first*1000;
          }
          else
          {
            frame[i][j] = 0;
          }
        }
      }
    }
    else
    {
      int xsize = heatmapVector->size() - 1;
      int ysize = heatmapVector->at(0).size() -1 ;
      for(int i = 0; i < heatmapVector->size(); i++)
      {
        for(int j = 0; j < heatmapVector->at(0).size(); j++)
        {
          if(!std::isinf(heatmapVector->at(i)[j].first) && !std::isinf(heatmapVector->at(i)[j].second) && heatmapVector->at(i)[j].first < 1 && heatmapVector->at(i)[j].first > -1)
          {
            frame[xsize - i][j] = radius*1000 - heatmapVector->at(i)[j].first*1000;
          }
          else
          {
            frame[xsize - i][j] = 0;
          }
        }
      }
    }
    int xsize = heatmapVector->size() - 1;
    int ysize = heatmapVector->at(0).size() -1 ;
    std::string str1, str2, str3, ticstr;
    Gnuplot gp;
    gp << "unset key\n";
    gp << "cd '../images'\n";
    gp << "set cbrange [-2:50]\n";
    gp << "set palette defined (-2 'navy', 4 'blue', 16 'green', 20 'yellow', 30 'orange', 40 'red')\n";
    gp << "set pm3d map\n";
    gp << "set hidden3d\n";
    gp << "set xrange [ 0 : 359 ] \n";


    // gp << "set view map\n";
    // gp << "set x2tics 2\n";
    // gp << "set xtics ('-1' 0, '1' 359)\n";

    str1 = "set yrange [ ";
    str2 = std::to_string(begin);
    str2 += " : ";
    str3 = std::to_string(end);
    str3 += " ] \n";

    gp << str1 + str2 + str3;

    ticstr = "set ytics (";
    if(!forward_reverse)
    {
      for(int i = begin; i < end-2; i+=4)
      {
        ticstr += "'";
        ticstr += double2strPercision(original_request_csv[2][i], 4);
        ticstr += "' ";
        ticstr += std::to_string(i);
        ticstr += ", ";
      }
      ticstr += "'";
      ticstr += double2strPercision(original_request_csv[2][end], 4);
      ticstr += "' ";
      ticstr += std::to_string(end);
      ticstr += ") \n";
    }
    else
    {
      for(int i = begin; i < end-2; i+=4)
      {
        ticstr += "'";
        ticstr += double2strPercision(original_request_csv[2][i], 4);
        ticstr += "' ";
        ticstr += std::to_string(end - i + begin);
        ticstr += ", ";
      }
      ticstr += "'";
      ticstr += double2strPercision(original_request_csv[2][end], 4);
      ticstr += "' ";
      ticstr += std::to_string(begin);
      ticstr += ") \n";
    }
    gp << ticstr;
    gp << "set terminal png \n";
    if(!forward_reverse)
      str1 = "set output 'forward_";
    else
      str1 = "set output 'reverse_";
    if(!(section/100))
    {
      str2 = "0";
    }
    if(!(section/10))
    {
      str2 = "00";
    }
    str2 += std::to_string(section);
    str3 = ".png' \n";
    gp << str1 + str2 + str3;
    if(!forward_reverse)     gp << "set title 'RPLidar Surface Model - Forward Run'\n";
    else     gp << "set title 'RPLidar Surface Model - Reverse Run'\n";
    gp << "set xlabel 'Unwraped pipe (Degrees)'\n";
    gp << "set ylabel 'Robot position along pipe (m)' offset 0.0, 0.0\n";
    gp << "splot '-'\n";
    gp.send2d(frame);
  }
  std::string HeatMap::double2strPercision(double number, int percision)
  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(percision) << number;
    std::string s = stream.str();
    return s;
  }
