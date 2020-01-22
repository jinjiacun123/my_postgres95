#ifndef TQUAL_H
#define TQUAL_H

typedef Pointer TimeQual;
#define NowTimeQual ((TimeQual)NULL)

extern TimeQual SelfTimeQual;
extern bool     heapisoverride(void);
extern bool     TimeQualIsLegal(TimeQual qual);
extern bool     TimeQualIndicatesDisableValidityChecking(TimeQual qual);
extern bool     TimeQualIsSnapshot(TimeQual qual);
extern bool     TimeQualIncludesNow(TimeQual qual);

#endif
