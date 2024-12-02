#include "drawcurve.h"

drawcurve::drawcurve(QCustomPlot* plot1,QCustomPlot* plot2,QCustomPlot* plot3)
{
    curveplot1 =plot1;
    curveplot2 =plot2;
    curveplot3 = plot3;
//    connect(&dataTimer2, SIGNAL(timeout()), this, SLOT(timeToAddData()));
//    connect(&rePlotTimer1, SIGNAL(timeout()), this, SLOT(timeToRePlot()));
//    connect(&dataTimer1, SIGNAL(timeout()), this, SLOT(timeToAddData()));
//    connect(&rePlotTimer2, SIGNAL(timeout()), this, SLOT(timeToRePlot()));
    connect(&dataTimer1, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    connect(&dataTimer2, SIGNAL(timeout()), this, SLOT(realtimeDataSlot2()));
    connect(&dataTimer3, SIGNAL(timeout()), this, SLOT(realtimeDataSlot3()));
    plot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    m_start2 = false;
    m_start1 = false;
    m_start3 = false;
}
void drawcurve::receiveresistance(double resistanceslot,double time)
{
    resistance = resistanceslot;
    key = time;
}
void drawcurve:: receivecurrent(double currentslot,double time)
{
    current = currentslot;
    key2 = time;
}
void drawcurve::receiveposition(int32_t position)
{
    positionreceive = position;
}
void drawcurve:: timeToAddData()
{
    QCustomPlot* customPlot = curveplot1;
    QCustomPlot* customPlot2 = curveplot2;
    //QTime time= QTime::currentTime();
    //qsrand(time.msec()+time.second()*1000);//随机数种子
    if(m_start1)
    {
        for(int i=0;i<customPlot->graphCount();i++)
          {
              for(int j=0;j<10;j++)//每次添加10个数据
              {
//                  if(!resistance.isEmpty())
//                  {
//                   customPlot->graph(i)->addData(customPlot->graph(i)->dataCount(),resistance[i]);
//                  }
                  if(resistance != 0)
                  {
                   customPlot->graph(i)->addData(customPlot->graph(i)->dataCount(),resistance);
                  }

                  //customPlot->graph(i)->addData(customPlot->graph(i)->dataCount(),qrand()/(double)RAND_MAX + i*2);
              }
          }
    }
//      if(m_start2)
//      {
//          for(int i=0;i<customPlot2->graphCount();i++)
//          {
//              for(int j=0;j<10;j++)//每次添加10个数据
//              {
//                  if(!current.isEmpty())
//                  {
//                   customPlot2->graph(i)->addData(customPlot2->graph(i)->dataCount(),current[i]);
//                  }

//                  //customPlot->graph(i)->addData(customPlot->graph(i)->dataCount(),qrand()/(double)RAND_MAX + i*2);
//              }
//          }
//      }


}

void drawcurve:: timeToRePlot()
{
    static QTime time(QTime::currentTime());
       double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

       QCustomPlot* customPlot = curveplot1;
       QCustomPlot* customPlot2 = curveplot2;
       int size = rangenum;
       //int size = 1000;
       if(m_start1)
       {
           customPlot->xAxis->setRange(customPlot->graph(0)->dataCount(), size, Qt::AlignRight);
           //重绘
           customPlot->replot(QCustomPlot::rpQueuedReplot);
       }
       if(m_start2)
       {
           customPlot2->xAxis->setRange(customPlot2->graph(0)->dataCount(), size, Qt::AlignRight);
           //重绘
           customPlot2->replot(QCustomPlot::rpQueuedReplot);
       }
       //customPlot->replot();
//       static double lastFpsKey;
//       static int frameCount;
//       ++frameCount;
}

void drawcurve:: startdraw()
{
    QCustomPlot* customPlot = curveplot1;
    QCustomPlot* customPlot2 = curveplot2;
//       if(m_start1)
//       {
//           customPlot->clearGraphs();//清除所有graph
//           m_countGraph = 1;//曲线数
//           QPen pen;
//           pen.setWidth(1);
//           //添加曲线
//           for(int i=0;i<m_countGraph;i++)
//           {
//               customPlot->addGraph();
//               //颜色随机
//               pen.setColor(QColor(qrand()%150+100,qrand()%150+100,qrand()%150+100));
//               customPlot->graph(i)->setPen(pen);//
//               //颜色随机

//           }
//           //设置y轴范围
//           customPlot->yAxis->setRange(-1, m_countGraph*2);
//           //设置x轴范围
//           int size = rangenum;
//           //int size = 1000;
//           customPlot->xAxis->setRange(0, size, Qt::AlignRight);
//           //定时添加和刷新数据
//           rePlotTimer1.start(30); // 间隔16ms刷新一次
//           dataTimer1.start(15); // 间隔时间5ms添加一次数据
//           //m_start2 = false;
//           //ui->btn_start2->setText("停止");
//       }
//       else
//       {
//           rePlotTimer1.stop(); // 停止重绘
//           dataTimer1.stop(); // 停止添加数据
//           //m_start2 = false;
//           //ui->btn_start2->setText("开始");
//       }

//       if(m_start2)
//       {
//           customPlot2->clearGraphs();
//           m_countGraph = 1;//曲线数
//           QPen pen;
//           pen.setWidth(1);
//           //添加曲线
//           for(int i=0;i<m_countGraph;i++)
//           {
//               //颜色随机
//               customPlot2->addGraph();
//               pen.setColor(QColor(qrand()%150+100,qrand()%150+100,qrand()%150+100));
//               customPlot2->graph(i)->setPen(pen);//

//           }
//           //设置y轴范围
//           customPlot2->yAxis->setRange(-1, m_countGraph*2);
//           //设置x轴范围
//           int size = rangenum;
//           //int size = 1000;
//           customPlot2->xAxis->setRange(0, size, Qt::AlignRight);
//           //定时添加和刷新数据
//           rePlotTimer2.start(30); // 间隔16ms刷新一次
//           dataTimer2.start(15); // 间隔时间5ms添加一次数据
//           //m_start2 = false;
//           //ui->btn_start2->setText("停止");
//       }
//       else
//       {
//           rePlotTimer2.stop(); // 停止重绘
//           dataTimer2.stop(); // 停止添加数据
//           //m_start2 = false;
//           //ui->btn_start2->setText("开始");
//       }

    //new
    if(m_start1)
    {
        dataTimer1.start(0);
       // m_start1=true;
        //ui->btn_start1->setText("停止");
    }
    else
    {
        dataTimer1.stop();
        //m_start1=false;
       // ui->btn_start1->setText("开始");
    }
    if(m_start2)
    {
        dataTimer2.start(0);
       // m_start1=true;
        //ui->btn_start1->setText("停止");
    }
    else
    {
        dataTimer2.stop();
        //m_start1=false;
       // ui->btn_start1->setText("开始");
    }
    if(m_start3)
    {
      dataTimer3.start(0);
    }
    else {
        dataTimer3.stop();
    }

}
void drawcurve:: realtimeDataSlot()
{
    QCustomPlot* customPlot =curveplot1;
    //static QTime time(QTime::currentTime());
    static int startflag = 0;
    //double key = time.elapsed()/1000.0; // 开始到现在的时间，单位秒
    static double lastPointKey = 0;
    static QFile handle("resistance.txt");
    if(startflag==0){
        handle.open(QIODevice::WriteOnly);
        startflag++;
    }
    static QTextStream write_(&handle);
    if (key!=0) // 大约2ms添加一次数据
    {
        // 添加数据到graph
//        customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
//        customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
        //记录当前时刻
//        if(!resistance.isEmpty())
//        {
//         customPlot->graph(0)->addData(key,resistance.last());
//        }
        if(resistance != 0)
        {
         customPlot->graph(0)->addData(key,resistance);
        }
        //qDebug()<<"time:"<<key<<"resistance"<<resistance.last()<<endl;
     //customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
        write_<<key<<" "<<resistance<<endl;
        lastPointKey = key;
    }
    customPlot->graph(0)->rescaleValueAxis(true, true);//y的极大值显示出来，此时y的极大值在最大范围处
    customPlot->graph(0)->rescaleAxes();//y轴自适应，极大值显示在y轴的范围中心
    // 曲线能动起来的关键在这里，设定x轴范围为最近8个时刻
    customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    //绘图
    customPlot->replot(QCustomPlot::rpQueuedReplot);
    if(endflag1)
    {
        handle.close();
    }
}
void drawcurve::realtimeDataSlot2()
{
    QCustomPlot* customPlot =curveplot2;
//    static QTime time(QTime::currentTime());
    static int startflag = 0;
    //double key = time.elapsed()/1000.0; // 开始到现在的时间，单位秒
    static double lastPointKey = 0;
    static QFile handle("current.txt");
    if(startflag==0){
        handle.open(QIODevice::WriteOnly);
        startflag++;
    }
    static QTextStream write_(&handle);
    if (key2!=0) // 大约2ms添加一次数据
    {
        // 添加数据到graph
//        customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
//        customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
        //记录当前时刻
//        if(!current.isEmpty())
//        {
//         customPlot->graph(0)->addData(key,current.last());
//        }
        if(current != 0)
        {
         customPlot->graph(0)->addData(key2,current);
        }
     //customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
       write_<<key2<<" "<<current<<endl;
       lastPointKey = key2;
    }
   customPlot->graph(0)->rescaleValueAxis(true, true);//y的极大值显示出来，此时y的极大值在最大范围处
   customPlot->graph(0)->rescaleAxes();//y轴自适应，极大值显示在y轴的范围中心
    // 曲线能动起来的关键在这里，设定x轴范围为最近8个时刻
    customPlot->xAxis->setRange(key2, 8, Qt::AlignRight);
    //绘图
    customPlot->replot(QCustomPlot::rpQueuedReplot);
    if(endflag2)
    {
        handle.close();
    }
}
void drawcurve::realtimeDataSlot3()//绘图电流位置
{
    QCustomPlot* customPlot =curveplot3;
    static QTime time(QTime::currentTime());
    static int startflag = 0;
    double key = time.elapsed()/1000.0; // 开始到现在的时间，单位秒
    static double lastPointKey = 0;
    static QFile handle("/txt/motorposition.txt");
    if(startflag==0){
        handle.open(QIODevice::WriteOnly);
        startflag++;
    }
    static QTextStream write_(&handle);
    if (key-lastPointKey > 0.002) // 大约2ms添加一次数据
    {
        // 添加数据到graph
//        customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
//        customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
        //记录当前时刻
//        if(!current.isEmpty())
//        {
//         customPlot->graph(0)->addData(key,current.last());
//        }
        if(positionreceive != 0)
        {
         customPlot->graph(0)->addData(key,positionreceive);
        }
     //customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
       write_<<key<<" "<<current<<endl;
       lastPointKey = key;
    }
   customPlot->graph(0)->rescaleValueAxis(true, true);//y的极大值显示出来，此时y的极大值在最大范围处
   customPlot->graph(0)->rescaleAxes();//y轴自适应，极大值显示在y轴的范围中心
    // 曲线能动起来的关键在这里，设定x轴范围为最近8个时刻
    customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    //绘图
    customPlot->replot(QCustomPlot::rpQueuedReplot);
    if(endflag3)
    {
        handle.close();
    }
}
void drawcurve::decision()
{
    switch (curveSelection) {
    case 100:
        timecurve=new QTimer();
        timecurve->setInterval(5);
        connect(timecurve,&QTimer::timeout,this,&drawcurve::decision);
        timecurve->start();
        curveSelection=-1;
        cout<<"waiting for patchClamp "<<endl;
        break;
    case 1:
        startdraw();
        curveSelection=-1;
        break;
    case 2:

        break;
    case 3:

        break;
    default:
        curveSelection=-2;
        break;
    }
}给我注释代码
