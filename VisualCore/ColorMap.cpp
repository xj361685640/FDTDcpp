//
// Created by yutong pang on 6/26/15.
//
#include "ColorMap.h"
void ColorMap::drawchart(std::vector<std::vector<double>>& ColorMapVector){
    FILE * temp = fopen("data.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    unsigned long xsize = ColorMapVector[0].size();
    unsigned long ysize = ColorMapVector.size();
    int xindex;
    int yindex;
    for (yindex=0; yindex<ysize; yindex++){
        for (xindex=0; xindex<xsize; xindex++){
            fprintf(temp, "%lf ", ColorMapVector[yindex][xindex]);
        }
            fprintf(temp, "\n");
    }
    fclose(temp);
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "set title \"FDTD SIMULATION COLOR MAP\" \n");//Send commands to gnuplot one by one.
    fprintf(gnuplotPipe, "set palette defined (-3 \"blue\", 0 \"white\", 1 \"red\") \n");
    fprintf(gnuplotPipe, "set xrange [0:%lu] \n", xsize);
    fprintf(gnuplotPipe, "set yrange [0:%lu] \n", ysize);
    fprintf(gnuplotPipe, "plot 'data.temp' matrix with image\n");
    pclose(gnuplotPipe);
}