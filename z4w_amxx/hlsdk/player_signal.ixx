
export module hlsdk.player_signal;

export namespace hlsdk {

	constexpr auto SIGNAL_BUY = (1 << 0);
	constexpr auto SIGNAL_BOMB = (1 << 1);
	constexpr auto SIGNAL_RESCUE = (1 << 2);
	constexpr auto SIGNAL_ESCAPE = (1 << 3);
	constexpr auto SIGNAL_VIPSAFETY = (1 << 4);

	class CUnifiedSignals
	{
	public:
		CUnifiedSignals()
		{
			m_flSignal = 0;
			m_flState = 0;
		}
	public:
		void Update()
		{
			m_flState = m_flSignal;
			m_flSignal = 0;
		}
		void Signal(int flags) { m_flSignal |= flags; }
		int GetSignal() const { return m_flSignal; }
		int GetState() const { return m_flState; }

	private:
		int m_flSignal;
		int m_flState;
	};

}