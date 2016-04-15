#ifndef FILTER_H
#define FILTER_H


enum filterTypes : int { lowPass = 0, highPass, bandPass, noFilter, NB_OF_FILTER_TYPE };

// Filtre d'ordre 2
class Filter
{
public:
    Filter();
    ~Filter();

    double filterValue(double value);

    void setCutoff(double cutoff);
    inline double getCutoff() { return _cutoff; }

    static void setSampleRate(double sampleRate);
    inline static double getSampleRate() { return _sampleRate; }

    void setFilterType(int type);
    void setResonance(double resonance);

    void reset();
    void updateCoef();

private:
    int _filterType;
    static double _sampleRate;
    double _cutoff;
    double _resonance;

    double _b[3];
    double _a[2];

    double _prevIn[2];
    double _prevOut[2];
};

#endif  // FILTER_H
