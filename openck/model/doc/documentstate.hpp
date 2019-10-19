#ifndef DOCUMENT_STATE_H
#define DOCUMENT_STATE_H

enum DocumentState
{
	DocState_Modified = 1,
	DocState_Locked = 2,

	DocState_Loading = 256
};

#endif // DOCUMENT_STATE_H