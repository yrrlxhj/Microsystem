#include "decision_task.h" // 包含 Decision_Task 类的头文件
#include "mainwindow.h"    // 包含主窗口相关的头文件

// Decision_Task 类的构造函数，初始化功能模块和线程
Decision_Task::Decision_Task(QCustomPlot* plot1, QCustomPlot* plot2, QCustomPlot* plot3) {
    plotdecision = plot1;  // 初始化第一个绘图控件
    plotdecision2 = plot2; // 初始化第二个绘图控件
    plotdecision3 = plot3; // 初始化第三个绘图控件

    parse_args(&params);   // 初始化微操作器的参数
    parse_args(&paramsfeed); // 初始化进料微操作器的参数

    if (actOpen) {         // 检查微操作器是否可以启动连接
        Ump_Init(&params); // 启动微操作器连接
    }

    m_control = new SBaslerCameraControl(this); // 初始化 Basler 相机模块

    // 初始化 Nikon 相机模块
    nikoncamera = new nikoncameracontrol(this);

    // 初始化自动聚焦模块，依赖 Basler 相机和 Nikon 相机
    A_Focus = new Auto_Focus(m_control, nikoncamera, params);

    // 创建一个线程用于自动聚焦模块
    QThread* afocusThread = new QThread;
    A_Focus->moveToThread(afocusThread); // 将 A_Focus 对象移动到新线程
    connect(afocusThread, &QThread::finished, afocusThread, &QThread::deleteLater); // 线程结束时释放资源
    connect(afocusThread, &QThread::started, A_Focus, &Auto_Focus::decision); // 启动线程时调用 decision 函数
    afocusThread->start(); // 启动线程

    // 初始化自动聚焦的独立界面
    U_Frame = new ui_frame(A_Focus);

    // 初始化平面定位模块，依赖自动聚焦模块、Basler 相机和 Nikon 相机
    pose_plane = new Pose_Plane(A_Focus, m_control, nikoncamera, params);

    // 创建一个线程用于平面定位模块
    QThread* planeThread = new QThread;
    pose_plane->moveToThread(planeThread); // 将 pose_plane 对象移动到新线程
    connect(planeThread, &QThread::finished, planeThread, &QThread::deleteLater); // 线程结束时释放资源
    connect(planeThread, &QThread::started, pose_plane, &Pose_Plane::decision); // 启动线程时调用 decision 函数
    connect(pose_plane, &Pose_Plane::sendpoint, A_Focus, &Auto_Focus::receivepoints); // 接收三角形顶点信息
    planeThread->start(); // 启动线程

    // 初始化电化学模块
    ch_instrument = new Ch_Instrument();

    // 创建一个线程用于电化学模块
    QThread* chiThread = new QThread;
    ch_instrument->moveToThread(chiThread); // 将 ch_instrument 对象移动到新线程
    connect(chiThread, &QThread::finished, chiThread, &QThread::deleteLater); // 线程结束时释放资源
    connect(chiThread, &QThread::started, ch_instrument, &Ch_Instrument::decision); // 启动线程时调用 decision 函数
    connect(ch_instrument, &Ch_Instrument::currentmutation, pose_plane, &Pose_Plane::touchCurrentMutation); // 处理电流突变
    connect(ch_instrument, &Ch_Instrument::dataGet, pose_plane, &Pose_Plane::sicmData); // 接收数据并传递到平面定位模块
    chiThread->start(); // 启动线程

    // 初始化图像采集模块，依赖 Basler 相机、Nikon 相机和进料参数
    imageCollect = new Pose_Kalman(m_control, nikoncamera, paramsfeed);

    // 创建一个线程用于图像采集模块
    QThread* imageCollectThread = new QThread;
    imageCollect->moveToThread(imageCollectThread); // 将 imageCollect 对象移动到新线程
    connect(imageCollectThread, &QThread::finished, imageCollectThread, &QThread::deleteLater); // 线程结束时释放资源
    connect(imageCollectThread, &QThread::started, imageCollect, &Pose_Kalman::decision); // 启动线程时调用 decision 函数
    connect(pose_plane, &Pose_Plane::sendTarget, imageCollect, &Pose_Kalman::receiveTargetP); // 接收目标点信息
    imageCollectThread->start(); // 启动线程

    // 当自动聚焦完成时触发决策选择
    connect(A_Focus, &Auto_Focus::afOver, this, &Decision_Task::decisionSelect);
}
// 总结
// 每个功能模块（如自动聚焦、电化学模块等）都独立运行在自己的线程中，保持高效并发性。
// 通过信号与槽机制实现模块间的灵活通信。
// 代码结构清晰，模块划分明确，利于扩展功能和维护。
// 从代码来看，Decision_Task 类实现了一个多线程模块化的架构，其中每个模块在单独的线程中运行，且通过信号与槽进行通信。这种设计方式增强了程序的并发性能和模块化，同时也适合扩展复杂功能。以下是一些关键点分析：

// 关键点分析
// 模块初始化：

// 包含多个功能模块，如相机控制、自动聚焦、平面定位、电化学模块等。
// 每个模块使用独立的线程，通过 QThread 和 moveToThread 实现并发处理。
// 模块交互：

// 通过信号与槽连接模块间的事件流。
// 例如：
// Pose_Plane 的 sendpoint 信号连接到 Auto_Focus 的 receivepoints 槽。
// Ch_Instrument 的 currentmutation 信号触发 Pose_Plane 的相关方法。
// 自动聚焦线程：

// 使用 Auto_Focus 类完成自动聚焦功能。线程启动后执行 decision 方法。
// 平面定位与电化学模块：

// 平面定位 (Pose_Plane) 通过与电化学模块 (Ch_Instrument) 协作实现某些数据驱动功能。
// 图像采集：

// Pose_Kalman 类整合相机控制并处理图像采集任务，支持多线程操作。
