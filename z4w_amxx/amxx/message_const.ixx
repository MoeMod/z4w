module;

export module amxx.message_const;
import hlsdk.types;

export namespace amxx {
	constexpr auto SVC_NOP = 1;
	constexpr auto SVC_DISCONNECT = 2;
	constexpr auto SVC_EVENT = 3;
	constexpr auto SVC_VERSION = 4;
	constexpr auto SVC_SETVIEW = 5;
	constexpr auto SVC_SOUND = 6;
	constexpr auto SVC_TIME = 7;
	constexpr auto SVC_PRINT = 8;
	constexpr auto SVC_STUFFTEXT = 9;
	constexpr auto SVC_SETANGLE = 10;
	constexpr auto SVC_SERVERINFO = 11;
	constexpr auto SVC_LIGHTSTYLE = 12;
	constexpr auto SVC_UPDATEUSERINFO = 13;
	constexpr auto SVC_DELTADESCRIPTION = 14;
	constexpr auto SVC_CLIENTDATA = 15;
	constexpr auto SVC_STOPSOUND = 16;
	constexpr auto SVC_PINGS = 17;
	constexpr auto SVC_PARTICLE = 18;
	constexpr auto SVC_DAMAGE = 19;
	constexpr auto SVC_SPAWNSTATIC = 20;
	constexpr auto SVC_EVENT_RELIABLE = 21;
	constexpr auto SVC_SPAWNBASELINE = 22;
	constexpr auto SVC_TEMPENTITY = 23;
	constexpr auto SVC_SETPAUSE = 24;
	constexpr auto SVC_SIGNONNUM = 25;
	constexpr auto SVC_CENTERPRINT = 26;
	constexpr auto SVC_KILLEDMONSTER = 27;
	constexpr auto SVC_FOUNDSECRET = 28;
	constexpr auto SVC_SPAWNSTATICSOUND = 29;
	constexpr auto SVC_INTERMISSION = 30;
	constexpr auto SVC_FINALE = 31;
	constexpr auto SVC_CDTRACK = 32;
	constexpr auto SVC_RESTORE = 33;
	constexpr auto SVC_CUTSCENE = 34;
	constexpr auto SVC_WEAPONANIM = 35;
	constexpr auto SVC_DECALNAME = 36;
	constexpr auto SVC_ROOMTYPE = 37;
	constexpr auto SVC_ADDANGLE = 38;
	constexpr auto SVC_NEWUSERMSG = 39;
	constexpr auto SVC_PACKETENTITIES = 40;
	constexpr auto SVC_DELTAPACKETENTITIES = 41;
	constexpr auto SVC_CHOKE = 42;
	constexpr auto SVC_RESOURCELIST = 43;
	constexpr auto SVC_NEWMOVEVARS = 44;
	constexpr auto SVC_RESOURCEREQUEST = 45;
	constexpr auto SVC_CUSTOMIZATION = 46;
	constexpr auto SVC_CROSSHAIRANGLE = 47;
	constexpr auto SVC_SOUNDFADE = 48;
	constexpr auto SVC_FILETXFERFAILED = 49;
	constexpr auto SVC_HLTV = 50;
	constexpr auto SVC_DIRECTOR = 51;
	constexpr auto SVC_VOICEINIT = 52;
	constexpr auto SVC_VOICEDATA = 53;
	constexpr auto SVC_SENDEXTRAINFO = 54;
	constexpr auto SVC_TIMESCALE = 55;

	/* Temp entity message types for message_begin() */
	constexpr auto	TE_BEAMPOINTS = 0;        // Beam effect between two points
	// write_byte(TE_BEAMPOINTS)
	// write_coord(startposition.x)
	// write_coord(startposition.y)
	// write_coord(startposition.z)
	// write_coord(endposition.x)
	// write_coord(endposition.y)
	// write_coord(endposition.z)
	// write_short(sprite index) 
	// write_byte(starting frame) 
	// write_byte(frame rate in 0.1's) 
	// write_byte(life in 0.1's) 
	// write_byte(line width in 0.1's) 
	// write_byte(noise amplitude in 0.01's) 
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(brightness)
	// write_byte(scroll speed in 0.1's)

	constexpr auto	TE_BEAMENTPOINT = 1;        // Beam effect between point and entity
	// write_byte(TE_BEAMENTPOINT)
	// write_short(start entity) 
	// write_coord(endposition.x)
	// write_coord(endposition.y)
	// write_coord(endposition.z)
	// write_short(sprite index) 
	// write_byte(starting frame) 
	// write_byte(frame rate in 0.1's) 
	// write_byte(life in 0.1's) 
	// write_byte(line width in 0.1's) 
	// write_byte(noise amplitude in 0.01's) 
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(brightness)
	// write_byte(scroll speed in 0.1's)

	constexpr auto	TE_GUNSHOT = 2;        // Particle effect plus ricochet sound
	// write_byte(TE_GUNSHOT)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)

	constexpr auto	TE_EXPLOSION = 3;        // Additive sprite, 2 dynamic lights, flickering particles, explosion sound, move vertically 8 pps
	// write_byte(TE_EXPLOSION)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_short(sprite index)
	// write_byte(scale in 0.1's)
	// write_byte(framerate)
	// write_byte(flags)
	//
	// The Explosion effect has some flags to control performance/aesthetic features:
	constexpr auto TE_EXPLFLAG_NONE = 0;        // All flags clear makes default Half-Life explosion
	constexpr auto TE_EXPLFLAG_NOADDITIVE = 1;        // Sprite will be drawn opaque (ensure that the sprite you send is a non-additive sprite)
	constexpr auto TE_EXPLFLAG_NODLIGHTS = 2;        // Do not render dynamic lights
	constexpr auto TE_EXPLFLAG_NOSOUND = 4;        // Do not play client explosion sound
	constexpr auto TE_EXPLFLAG_NOPARTICLES = 8;        // Do not draw particles

	constexpr auto	TE_TAREXPLOSION = 4;        // Quake1 "tarbaby" explosion with sound
	// write_byte(TE_TAREXPLOSION)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)

	constexpr auto	TE_SMOKE = 5;        // Alphablend sprite, move vertically 30 pps
	// write_byte(TE_SMOKE)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z) 
	// write_short(sprite index)
	// write_byte(scale in 0.1's)
	// write_byte(framerate)

	constexpr auto	TE_TRACER = 6;        // Tracer effect from point to point
	// write_byte(TE_TRACER)
	// write_coord(startposition.x)
	// write_coord(startposition.y)
	// write_coord(startposition.z)
	// write_coord(endposition.x)
	// write_coord(endposition.y)
	// write_coord(endposition.z)

	constexpr auto	TE_LIGHTNING = 7;        // TE_BEAMPOINTS with simplified parameters
	// write_byte(TE_LIGHTNING)
	// write_coord(startposition.x)
	// write_coord(startposition.y)
	// write_coord(startposition.z)
	// write_coord(endposition.x)
	// write_coord(endposition.y)
	// write_coord(endposition.z)
	// write_byte(life in 0.1's) 
	// write_byte(width in 0.1's) 
	// write_byte(amplitude in 0.01's)
	// write_short(sprite model index)

	constexpr auto	TE_BEAMENTS = 8;
	// write_byte(TE_BEAMENTS)
	// write_short(start entity) 
	// write_short(end entity) 
	// write_short(sprite index) 
	// write_byte(starting frame) 
	// write_byte(frame rate in 0.1's) 
	// write_byte(life in 0.1's) 
	// write_byte(line width in 0.1's) 
	// write_byte(noise amplitude in 0.01's) 
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(brightness)
	// write_byte(scroll speed in 0.1's)

	constexpr auto	TE_SPARKS = 9;        // 8 random tracers with gravity, ricochet sprite
	// write_byte(TE_SPARKS)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z) 

	constexpr auto	TE_LAVASPLASH = 10;       // Quake1 lava splash
	// write_byte(TE_LAVASPLASH)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)

	constexpr auto	TE_TELEPORT = 11;       // Quake1 teleport splash
	// write_byte(TE_TELEPORT)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)

	constexpr auto TE_EXPLOSION2 = 12;       // Quake1 colormaped (base palette) particle explosion with sound
	// write_byte(TE_EXPLOSION2)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_byte(starting color)
	// write_byte(num colors)

	constexpr auto TE_BSPDECAL = 13;       // Decal from the .BSP file
	// write_byte(TE_BSPDECAL)
	// write_coord(position.x) decal position (center of texture in world)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_short(texture index of precached decal texture name)
	// write_short(entity index)
	// [optional - write_short(index of model of above entity) only included if previous short is non-zero (not the world)]

	constexpr auto TE_IMPLOSION = 14;       // Tracers moving toward a point
	// write_byte(TE_IMPLOSION)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_byte(radius)
	// write_byte(count)
	// write_byte(life in 0.1's) 

	constexpr auto TE_SPRITETRAIL = 15;       // Line of moving glow sprites with gravity, fadeout, and collisions
	// write_byte(TE_SPRITETRAIL)
	// write_coord(startposition.x)
	// write_coord(startposition.y)
	// write_coord(startposition.z)
	// write_coord(endposition.x)
	// write_coord(endposition.y)
	// write_coord(endposition.z)
	// write_short(sprite index)
	// write_byte(count)
	// write_byte(life in 0.1's) 
	// write_byte(scale in 0.1's) 
	// write_byte(velocity along vector in 10's)
	// write_byte(randomness of velocity in 10's)

	constexpr auto TE_SPRITE = 17;       // Additive sprite, plays 1 cycle
	// write_byte(TE_SPRITE)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_short(sprite index) 
	// write_byte(scale in 0.1's) 
	// write_byte(brightness)

	constexpr auto TE_BEAMSPRITE = 18;       // A beam with a sprite at the end
	// write_byte(TE_BEAMSPRITE)
	// write_coord(startposition.x)
	// write_coord(startposition.y)
	// write_coord(startposition.z)
	// write_coord(endposition.x)
	// write_coord(endposition.y)
	// write_coord(endposition.z) 
	// write_short(beam sprite index) 
	// write_short(end sprite index) 

	constexpr auto TE_BEAMTORUS = 19;       // Screen aligned beam ring, expands to max radius over lifetime
	// write_byte(TE_BEAMTORUS)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(axis.x)
	// write_coord(axis.y)
	// write_coord(axis.z) 
	// write_short(sprite index) 
	// write_byte(starting frame) 
	// write_byte(frame rate in 0.1's) 
	// write_byte(life in 0.1's) 
	// write_byte(line width in 0.1's) 
	// write_byte(noise amplitude in 0.01's) 
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(brightness)
	// write_byte(scroll speed in 0.1's)

	constexpr auto TE_BEAMDISK = 20;       // Disk that expands to max radius over lifetime
	// write_byte(TE_BEAMDISK)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(axis.x)
	// write_coord(axis.y)
	// write_coord(axis.z) 
	// write_short(sprite index) 
	// write_byte(starting frame) 
	// write_byte(frame rate in 0.1's) 
	// write_byte(life in 0.1's) 
	// write_byte(line width in 0.1's) 
	// write_byte(noise amplitude in 0.01's) 
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(brightness)
	// write_byte(scroll speed in 0.1's)

	constexpr auto TE_BEAMCYLINDER = 21;       // Cylinder that expands to max radius over lifetime
	// write_byte(TE_BEAMCYLINDER)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(axis.x)
	// write_coord(axis.y)
	// write_coord(axis.z) 
	// write_short(sprite index) 
	// write_byte(starting frame) 
	// write_byte(frame rate in 0.1's) 
	// write_byte(life in 0.1's) 
	// write_byte(line width in 0.1's) 
	// write_byte(noise amplitude in 0.01's) 
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(brightness)
	// write_byte(scroll speed in 0.1's)

	constexpr auto TE_BEAMFOLLOW = 22;       // Create a line of decaying beam segments until entity stops moving
	// write_byte(TE_BEAMFOLLOW)
	// write_short(entity:attachment to follow)
	// write_short(sprite index)
	// write_byte(life in 0.1's) 
	// write_byte(line width in 0.1's) 
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(brightness)

	constexpr auto TE_GLOWSPRITE = 23;
	// write_byte(TE_GLOWSPRITE)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_short(model index)
	// write_byte(scale / 10)
	// write_byte(size)
	// write_byte(brightness)

	constexpr auto TE_BEAMRING = 24;       // Connect a beam ring to two entities
	// write_byte(TE_BEAMRING)
	// write_short(start entity) 
	// write_short(end entity) 
	// write_short(sprite index) 
	// write_byte(starting frame) 
	// write_byte(frame rate in 0.1's) 
	// write_byte(life in 0.1's) 
	// write_byte(line width in 0.1's) 
	// write_byte(noise amplitude in 0.01's) 
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(brightness)
	// write_byte(scroll speed in 0.1's)

	constexpr auto TE_STREAK_SPLASH = 25;       // Oriented shower of tracers
	// write_byte(TE_STREAK_SPLASH)
	// write_coord(startposition.x)
	// write_coord(startposition.y)
	// write_coord(startposition.z)
	// write_coord(vector.x)
	// write_coord(vector.y)
	// write_coord(vector.z) 
	// write_byte(color)
	// write_short(count)
	// write_short(base speed)
	// write_short(ramdon velocity)

	constexpr auto TE_DLIGHT = 27;       // Dynamic light, effect world, minor entity effect
	// write_byte(TE_DLIGHT)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_byte(radius in 10's) 
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(brightness)
	// write_byte(life in 10's)
	// write_byte(decay rate in 10's)

	constexpr auto TE_ELIGHT = 28;       // Point entity light, no world effect
	// write_byte(TE_ELIGHT)
	// write_short(entity:attachment to follow)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(radius)
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)
	// write_byte(life in 0.1's)
	// write_coord(decay rate)

	constexpr auto TE_TEXTMESSAGE = 29;
	// write_byte(TE_TEXTMESSAGE)
	// write_byte(channel)
	// write_short(x) -1 = center)
	// write_short(y) -1 = center)
	// write_byte(effect) 0 = fade in/fade out, 1 is flickery credits, 2 is write out (training room)
	// write_byte(red) - text color
	// write_byte(green)
	// write_byte(blue)
	// write_byte(alpha)
	// write_byte(red) - effect color
	// write_byte(green)
	// write_byte(blue)
	// write_byte(alpha)
	// write_short(fadein time)
	// write_short(fadeout time)
	// write_short(hold time)
	// [optional] write_short(fxtime) time the highlight lags behing the leading text in effect 2
	// write_string(text message) 512 chars max string size

	constexpr auto TE_LINE = 30;
	// write_byte(TE_LINE)
	// write_coord(startposition.x)
	// write_coord(startposition.y)
	// write_coord(startposition.z)
	// write_coord(endposition.x)
	// write_coord(endposition.y)
	// write_coord(endposition.z)
	// write_short(life in 0.1 s)
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)

	constexpr auto TE_BOX = 31;
	// write_byte(TE_BOX)
	// write_coord(boxmins.x)
	// write_coord(boxmins.y)
	// write_coord(boxmins.z)
	// write_coord(boxmaxs.x)
	// write_coord(boxmaxs.y)
	// write_coord(boxmaxs.z)
	// write_short(life in 0.1 s)
	// write_byte(red)
	// write_byte(green)
	// write_byte(blue)

	constexpr auto TE_KILLBEAM = 99;       // Kill all beams attached to entity
	// write_byte(TE_KILLBEAM)
	// write_short(entity)

	constexpr auto TE_LARGEFUNNEL = 100;
	// write_byte(TE_LARGEFUNNEL)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_short(sprite index) 
	// write_short(flags) 

	constexpr auto	TE_BLOODSTREAM = 101;      // Particle spray
	// write_byte(TE_BLOODSTREAM)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(vector.x)
	// write_coord(vector.y)
	// write_coord(vector.z)
	// write_byte(color)
	// write_byte(speed)

	constexpr auto	TE_SHOWLINE = 102;      // Line of particles every 5 units, dies in 30 seconds
	// write_byte(TE_SHOWLINE)
	// write_coord(startposition.x)
	// write_coord(startposition.y)
	// write_coord(startposition.z)
	// write_coord(endposition.x)
	// write_coord(endposition.y)
	// write_coord(endposition.z)

	constexpr auto TE_BLOOD = 103;      // Particle spray
	// write_byte(TE_BLOOD)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(vector.x)
	// write_coord(vector.y)
	// write_coord(vector.z)
	// write_byte(color)
	// write_byte(speed)

	constexpr auto TE_DECAL = 104;      // Decal applied to a brush entity (not the world)
	// write_byte(TE_DECAL)
	// write_coord(position.x) decal position (center of texture in world)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_byte(texture index of precached decal texture name)
	// write_short(entity index)

	constexpr auto TE_FIZZ = 105;      // Create alpha sprites inside of entity, float upwards
	// write_byte(TE_FIZZ)
	// write_short(entity)
	// write_short(sprite index)
	// write_byte density)

	constexpr auto TE_MODEL = 106;      // Create a moving model that bounces and makes a sound when it hits
	// write_byte(TE_MODEL)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(velocity.x)
	// write_coord(velocity.y)
	// write_coord(velocity.z)
	// write_angle(initial yaw)
	// write_short(model index)
	// write_byte(bounce sound type)
	// write_byte(life in 0.1's)

	constexpr auto TE_EXPLODEMODEL = 107;      // Spherical shower of models, picks from set
	// write_byte(TE_EXPLODEMODEL)
	// write_coord(origin.x)
	// write_coord(origin.y)
	// write_coord(origin.z)
	// write_coord(velocity.x)
	// write_coord(velocity.y)
	// write_coord(velocity.z)
	// write_short(model index)
	// write_short(count)
	// write_byte(life in 0.1's)

	constexpr auto TE_BREAKMODEL = 108;      // Box of models or sprites
	// write_byte(TE_BREAKMODEL)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(size.x)
	// write_coord(size.y)
	// write_coord(size.z)
	// write_coord(velocity.x)
	// write_coord(velocity.y)
	// write_coord(velocity.z)
	// write_byte(random velocity in 10's)
	// write_short(sprite or model index)
	// write_byte(count)
	// write_byte(life in 0.1 secs)
	// write_byte(flags)

	constexpr auto TE_GUNSHOTDECAL = 109;      // Decal and ricochet sound
	// write_byte(TE_GUNSHOTDECAL)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_short(entity index???)
	// write_byte(decal???)

	constexpr auto TE_SPRITE_SPRAY = 110;      // Spray of alpha sprites
	// write_byte(TE_SPRITE_SPRAY)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(velocity.x)
	// write_coord(velocity.y)
	// write_coord(velocity.z)
	// write_short(sprite index)
	// write_byte(count)
	// write_byte(speed)
	// write_byte(noise)

	constexpr auto TE_ARMOR_RICOCHET = 111;      // Quick spark sprite, client ricochet sound.
	// write_byte(TE_ARMOR_RICOCHET)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_byte(scale in 0.1's)

	constexpr auto TE_PLAYERDECAL = 112;
	// write_byte(TE_PLAYERDECAL)
	// write_byte(playerindex)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_short(entity???)
	// write_byte(decal number)
	// [optional] write_short(model index)

	constexpr auto TE_BUBBLES = 113;      // Create alpha sprites inside of box, float upwards
	// write_byte(TE_BUBBLES)
	// write_coord(position.x) (min start position)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(position.x) (max start position)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(float height)
	// write_short(model index)
	// write_byte(count)
	// write_coord(speed)

	constexpr auto TE_BUBBLETRAIL = 114;      // Create alpha sprites along a line, float upwards
	// write_byte(TE_BUBBLETRAIL)
	// write_coord(position.x) (min start position)
	// write_coord(position.y) (min start position)
	// write_coord(position.z) (min start position)
	// write_coord(position.x) (max start position)
	// write_coord(position.y) (max start position)
	// write_coord(position.z) (max start position)
	// write_coord(float height)
	// write_short(model index)
	// write_byte(count)
	// write_coord(speed)

	constexpr auto TE_BLOODSPRITE = 115;      // Spray of opaque sprite1's that fall, single sprite2 for 1..2 secs (this is a high-priority tent)
	// write_byte(TE_BLOODSPRITE)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_short(sprite1 index)
	// write_short(sprite2 index)
	// write_byte(color)
	// write_byte(scale)

	constexpr auto TE_WORLDDECAL = 116;      // Decal applied to the world brush
	// write_byte(TE_WORLDDECAL)
	// write_coord(position.x) decal position (center of texture in world)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_byte(texture index of precached decal texture name)

	constexpr auto TE_WORLDDECALHIGH = 117;      // Decal (with texture index > 256) applied to world brush
	// write_byte(TE_WORLDDECALHIGH)
	// write_coord(position.x) decal position (center of texture in world)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_byte(texture index of precached decal texture name - 256)

	constexpr auto TE_DECALHIGH = 118;      // Same as TE_DECAL, but the texture index was greater than 256
	// write_byte(TE_DECALHIGH)
	// write_coord(position.x) decal position (center of texture in world)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_byte(texture index of precached decal texture name - 256)
	// write_short(entity index)

	constexpr auto TE_PROJECTILE = 119;      // Makes a projectile (like a nail) (this is a high-priority tent)
	// write_byte(TE_PROJECTILE)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(velocity.x)
	// write_coord(velocity.y)
	// write_coord(velocity.z)
	// write_short(modelindex)
	// write_byte(life)
	// write_byte(owner)  projectile won't collide with owner (if owner == 0, projectile will hit any client).

	constexpr auto TE_SPRAY = 120;     // Throws a shower of sprites or models
	// write_byte(TE_SPRAY)
	// write_coord(position.x)
	// write_coord(position.y)
	// write_coord(position.z)
	// write_coord(direction.x)
	// write_coord(direction.y)
	// write_coord(direction.z)
	// write_short(modelindex)
	// write_byte(count)
	// write_byte(speed)
	// write_byte(noise)
	// write_byte(rendermode)

	constexpr auto TE_PLAYERSPRITES = 121;      // Sprites emit from a player's bounding box (ONLY use for players!)
	// write_byte(TE_PLAYERSPRITES)
	// write_short(playernum)
	// write_short(sprite modelindex)
	// write_byte(count)
	// write_byte(variance) (0 = no variance in size) (10 = 10% variance in size)

	constexpr auto TE_PARTICLEBURST = 122;      // Very similar to lavasplash
	// write_byte(TE_PARTICLEBURST)
	// write_coord(origin)
	// write_short(radius)
	// write_byte(particle color)
	// write_byte(duration * 10) (will be randomized a bit)

	constexpr auto TE_FIREFIELD = 123;      // Makes a field of fire
	// write_byte(TE_FIREFIELD)
	// write_coord(origin)
	// write_short(radius) (fire is made in a square around origin. -radius, -radius to radius, radius)
	// write_short(modelindex)
	// write_byte(count)
	// write_byte(flags)
	// write_byte(duration (in seconds) * 10) (will be randomized a bit)
	//
	// to keep network traffic low, this message has associated flags that fit into a byte:
	constexpr auto TEFIRE_FLAG_ALLFLOAT = 1;        // All sprites will drift upwards as they animate
	constexpr auto TEFIRE_FLAG_SOMEFLOAT = 2;        // Some of the sprites will drift upwards. (50% chance)
	constexpr auto TEFIRE_FLAG_LOOP = 4;        // If set, sprite plays at 15 fps, otherwise plays at whatever rate stretches the animation over the sprite's duration.
	constexpr auto TEFIRE_FLAG_ALPHA = 8;        // If set, sprite is rendered alpha blended at 50% else, opaque
	constexpr auto TEFIRE_FLAG_PLANAR = 16;       // If set, all fire sprites have same initial Z instead of randomly filling a cube. 

	constexpr auto TE_PLAYERATTACHMENT = 124;      // Attaches a TENT to a player (this is a high-priority tent)
	// write_byte(TE_PLAYERATTACHMENT)
	// write_byte(entity index of player)
	// write_coord(vertical offset) (attachment origin.z = player origin.z + vertical offset)
	// write_short(model index)
	// write_short(life * 10 )

	constexpr auto TE_KILLPLAYERATTACHMENTS = 125;      // Will expire all TENTS attached to a player.
	// write_byte(TE_KILLPLAYERATTACHMENTS)
	// write_byte(entity index of player)

	constexpr auto TE_MULTIGUNSHOT = 126;      // Much more compact shotgun message
	// This message is used to make a client approximate a 'spray' of gunfire.
	// Any weapon that fires more than one bullet per frame and fires in a bit of a spread is
	// a good candidate for MULTIGUNSHOT use. (shotguns)
	//
	// NOTE: This effect makes the client do traces for each bullet, these client traces ignore
	//		 entities that have studio models.Traces are 4096 long.
	//
	// write_byte(TE_MULTIGUNSHOT)
	// write_coord(origin.x)
	// write_coord(origin.y)
	// write_coord(origin.z)
	// write_coord(direction.x)
	// write_coord(direction.y)
	// write_coord(direction.z)
	// write_coord(x noise * 100)
	// write_coord(y noise * 100)
	// write_byte(count)
	// write_byte(bullethole decal texture index)

	constexpr auto TE_USERTRACER = 127;      // Larger message than the standard tracer, but allows some customization.
	// write_byte(TE_USERTRACER)
	// write_coord(origin.x)
	// write_coord(origin.y)
	// write_coord(origin.z)
	// write_coord(velocity.x)
	// write_coord(velocity.y)
	// write_coord(velocity.z)
	// write_byte(life * 10)
	// write_byte(color) this is an index into an array of color vectors in the engine. (0 - )
	// write_byte(length * 10)

	// From hltv.h from the HLSDK, these are used in conjunction with SVC_DIRECTOR
	// sub commands of svc_director:
	constexpr auto DRC_CMD_NONE = 0;	// NULL director command
	constexpr auto DRC_CMD_START = 1;	// start director mode
	constexpr auto DRC_CMD_EVENT = 2;	// informs about director command
	constexpr auto DRC_CMD_MODE = 3;	// switches camera modes
	constexpr auto DRC_CMD_CAMERA = 4;	// sets camera registers
	constexpr auto DRC_CMD_TIMESCALE = 5;	// sets time scale
	constexpr auto DRC_CMD_MESSAGE = 6;	// send HUD centerprint
	constexpr auto DRC_CMD_SOUND = 7;	// plays a particular sound
	constexpr auto DRC_CMD_STATUS = 8;	// status info about broadcast
	constexpr auto DRC_CMD_BANNER = 9;	// banner file name for HLTV gui
	constexpr auto	DRC_CMD_FADE = 10;	// send screen fade command
	constexpr auto DRC_CMD_SHAKE = 11;	// send screen shake command
	constexpr auto DRC_CMD_STUFFTEXT = 12;	// like the normal svc_stufftext but as director command

	constexpr auto DRC_CMD_LAST = 12;

	// HLTV_EVENT event flags
	constexpr auto DRC_FLAG_PRIO_MASK = 0x0F;	// priorities between 0 and 15 (15 most important)
	constexpr auto DRC_FLAG_SIDE = (1 << 4);	// 
	constexpr auto DRC_FLAG_DRAMATIC = (1 << 5);	// is a dramatic scene
	constexpr auto DRC_FLAG_SLOWMOTION = (1 << 6);  // would look good in SloMo
	constexpr auto DRC_FLAG_FACEPLAYER = (1 << 7);  // player is doning something (reload/defuse bomb etc)
	constexpr auto DRC_FLAG_INTRO = (1 << 8);	// is a introduction scene
	constexpr auto DRC_FLAG_FINAL = (1 << 9);	// is a final scene
	constexpr auto DRC_FLAG_NO_RANDOM = (1 << 10);	// don't randomize event data


	constexpr auto MAX_DIRECTOR_CMD_PARAMETERS = 4;
	constexpr auto MAX_DIRECTOR_CMD_STRING = 128;
}