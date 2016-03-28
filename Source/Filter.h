#ifndef FILTER_H
#define FILTER_H


enum filterTypes : int { lowPass = 0, highPass, bandPass, NB_OF_FILTER_TYPE };

// Filtre d'ordre 2
class Filter
{
public:
    Filter();
    ~Filter();

    double filterValue(double value);

    static void setSampleRate(double sampleRate);
    inline static void setFilterType(int type) { _filterType = type; }
    static void setCutoff(double cutoff);
    static void setResonance(double resonance);


private:
    static void updateCoef();

private:

    static int _filterType;
    static double _sampleRate;
    static double _cutoff;
    static double _resonance;

    static double _b[3];
    static double _a[2];

    double _prevIn[2];
    double _prevOut[2];
};

#endif  // FILTER_H
