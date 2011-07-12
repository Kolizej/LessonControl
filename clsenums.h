#ifndef CLSENUMS_H
#define CLSENUMS_H

class clsEnums
{
public:
    clsEnums();

    //уровень звука
    enum enumVolume
    {
        VolumeLow = 0,
        VolumeNormal = 1,
        VolumeHigh = 2
    };

    //темп лекции
    enum enumSpeed
    {
        SpeedLow = 0,
        SpeedNormal = 1,
        SpeedHigh = 2
    };

    //уровень понимания
    enum enumUnderstand
    {
        NotUnderstand = 0,
        Understand = 1
    };
};

#endif // CLSENUMS_H
