#pragma once

class Research
{
public:
    Research(unsigned research_time);
    virtual ~Research();

protected:
    unsigned researchTime;
};
