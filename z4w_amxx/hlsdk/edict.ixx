module;

export module hlsdk.edict;
import hlsdk.types;
import hlsdk.consts;
import hlsdk.progdefs;

export namespace hlsdk
{
	constexpr auto MAX_ENT_LEAFS = 48;

	typedef struct edict_s
	{
		qboolean		free;
		int		serialnumber;

		link_t		area;		// linked to a division node or leaf
		int		headnode;		// -1 to use normal leaf check

		int		num_leafs;
		short		leafnums[MAX_ENT_LEAFS];

		float		freetime;		// sv.time when the object was freed

		void* pvPrivateData;	// Alloced and freed by engine, used by DLLs
		entvars_t		v;		// C exported fields from progs

		// other fields from progs come immediately after
	} edict_t;
}