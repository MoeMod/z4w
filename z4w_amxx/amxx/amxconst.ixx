module;
export module amxx.amxconst;

export namespace amxx {

	constexpr auto PLUGIN_CONTINUE = 0;	/* Results returned by public functions */
	constexpr auto PLUGIN_HANDLED = 1;	/* stop other plugins */
	constexpr auto PLUGIN_HANDLED_MAIN = 2;	/* to use in client_command(), continue all plugins but stop the command */

}