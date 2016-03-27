#ifndef ENVELOPE_H
#define ENVELOPE_H


class Envelope
{
public:
    enum envelopeState {idle=0, attack, decay, sustain, release, NB_OF_ENV_STATE};

    Envelope();
    ~Envelope();

    void reset();
    double envelopeValue();

    void startAttack();
    void releaseNote();
    int getState();

    void setAttackLevel(double level);
    void setDecayLevel(double level);

    void setAttackRate(unsigned long long rate);
    void setDecayRate(unsigned long long rate);
    void setReleaseRate(unsigned long long rate);

    inline bool isCycleFinished() { return _finishedRelease; }

private:
    double multiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);

private:
    envelopeState _state;

    const double _minLevel;

    double _envValue;

    double _attackLevel;
    double _decayLevel;
    double _attackMultiplier;
    double _decayMultiplier;
    double _releaseMultiplier;
    unsigned long long _attackLength;
    unsigned long long _decayLength;
    unsigned long long _releaseLength;

    bool _finishedRelease;
};


#endif  // ENVELOPE_H
