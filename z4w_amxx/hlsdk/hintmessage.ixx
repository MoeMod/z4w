
export module hlsdk.hintmessage;
export import hlsdk.cbase;
export import hlsdk.utlvector;

export namespace hlsdk {

	class CHintMessage
	{
	public:
		CHintMessage(const char* hintString, bool isHint, CUtlVector<const char*>* args, duration_t duration);
		~CHintMessage(void);

	public:
		duration_t GetDuration(void) const { return m_duration; }
		void Send(CBaseEntity* client);
		bool IsEquivalent(const char* hintString, CUtlVector<const char*>* args) const;

	private:
		const char* m_hintString;
		CUtlVector<char*> m_args;
		duration_t m_duration;
		bool m_isHint;
	};

	class CHintMessageQueue
	{
	public:
		void Reset(void);
		void Update(CBaseEntity* player);
		bool AddMessage(const char* message, duration_t duration, bool isHint, CUtlVector<const char*>* args);
		bool IsEmpty(void) { return m_messages.Count() == 0; }

	private:
		time_point_t m_tmMessageEnd;
		CUtlVector<CHintMessage*> m_messages;
	};

}