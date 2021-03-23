
export module amxx.amxmodx_util;
import hlsdk.extdll;
import hlsdk.util;
import amxx.convert;
import amxx.message_const;

using namespace hlsdk;
using namespace std::chrono_literals;

export namespace amxx {

	char* UTIL_SplitHudMessage(const char* src)
	{
		static char message[512];
		short b = 0, d = 0, e = 0, c = -1;

		while (src[d] && e < 480)
		{
			if (src[d] == ' ')
			{
				c = e;
			}
			else if (src[d] == '\n')
			{
				c = -1;
				b = 0;
			}

			message[e++] = src[d++];

			if (++b == 69)
			{
				if (c == -1)
				{
					message[e++] = '\n';
					b = 0;
				}
				else {
					message[c] = '\n';
					b = e - c - 1;
					c = -1;
				}
			}
		}

		message[e] = 0;
		return message;
	}



	unsigned short FixedUnsigned16(float value, float scale)
	{
		int output = (int)(value * scale);

		if (output < 0)
			output = 0;
		else if (output > 0xFFFF)
			output = 0xFFFF;

		return (unsigned short)output;
	}

	short FixedSigned16(float value, float scale)
	{
		int output = (int)(value * scale);

		if (output > 32767)
			output = 32767;
		else if (output < -32768)
			output = -32768;

		return (short)output;
	}

	void UTIL_HudMessage(auto_ent<edict_t*> pEntity, const hudtextparms_t& textparms, const char* pMessage)
	{
		if (pEntity)
			MESSAGE_BEGIN(MSG_ONE_UNRELIABLE, SVC_TEMPENTITY, nullptr, pEntity);
		else
			MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);

		WRITE_BYTE(29);
		WRITE_BYTE(textparms.channel & 0xFF);
		WRITE_SHORT(FixedSigned16(textparms.x, (1 << 13)));
		WRITE_SHORT(FixedSigned16(textparms.y, (1 << 13)));
		WRITE_BYTE(textparms.effect);
		WRITE_BYTE(textparms.r1);
		WRITE_BYTE(textparms.g1);
		WRITE_BYTE(textparms.b1);
		WRITE_BYTE(0);
		WRITE_BYTE(255);
		WRITE_BYTE(255);
		WRITE_BYTE(250);
		WRITE_BYTE(0);
		WRITE_SHORT(FixedUnsigned16(textparms.fadeinTime / 1s, (1 << 8)));
		WRITE_SHORT(FixedUnsigned16(textparms.fadeoutTime / 1s, (1 << 8)));
		WRITE_SHORT(FixedUnsigned16(textparms.holdTime / 1s, (1 << 8)));

		if (textparms.effect == 2)
			WRITE_SHORT(FixedUnsigned16(textparms.fxTime / 1s, (1 << 8)));

		WRITE_STRING(pMessage);
		MESSAGE_END();
	}
}