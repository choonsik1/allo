
//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for Catapult High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//
#include <algorithm>
#include <ac_int.h>
#include <ac_fixed.h>
#include <ac_channel.h>
#include <ac_std_float.h>
#include <math.h>
#include <stdint.h>
using namespace std;

// --- Catapult compatibility shim for Allo-emitted Vitis types ---
template<int W> using ap_int  = ac_int<W, true>;
template<int W> using ap_uint = ac_int<W, false>;
typedef ac_std_float<16, 5> half;   // IEEE-754 binary16
// ----------------------------------------------------------------
void node_0_0(
  ac_channel< ac_int<26, false> >& v0,
  ac_channel< ac_int<26, false> >& v1,
  ac_channel< ac_int<26, false> >& v2,
  ac_channel< ac_int<26, false> >& v3,
  ac_channel< ac_int<17, false> >& v4,
  ac_channel< ac_int<17, false> >& v5,
  ac_channel< ac_int<17, false> >& v6,
  ac_channel< ac_int<17, false> >& v7,
  ac_channel< int32_t >& v8,
  ac_channel< int32_t >& v9,
  ac_channel< int32_t >& v10,
  ac_channel< int32_t >& v11,
  ac_channel< int32_t >& v12,
  ac_channel< int32_t >& v13,
  ac_channel< int32_t >& v14,
  ac_channel< int32_t >& v15,
  ac_channel< ac_int<26, false> >& v16,
  ac_channel< ac_int<26, false> >& v17,
  ac_channel< ac_int<26, false> >& v18,
  ac_channel< ac_int<26, false> >& v19,
  ac_channel< int32_t >& v20,
  ac_channel< int32_t >& v21,
  ac_channel< int32_t >& v22,
  ac_channel< int32_t >& v23,
  ac_channel< int32_t >& v24,
  ac_channel< int32_t >& v25,
  ac_channel< int32_t >& v26,
  ac_channel< int32_t >& v27,
  ac_channel< ac_int<17, false> >& v28,
  ac_channel< ac_int<17, false> >& v29,
  ac_channel< ac_int<17, false> >& v30,
  ac_channel< ac_int<17, false> >& v31
) {	// L2
  int32_t irf[8];	// L39
  for (int v33 = 0; v33 < 8; v33++) {	// L40
    irf[v33] = 0;	// L40
  }
  half drf[8];	// L41
  for (int v35 = 0; v35 < 8; v35++) {	// L42
    drf[v35] = (double)0.000000;	// L42
  }
  int32_t drf_full[8];	// L43
  for (int v37 = 0; v37 < 8; v37++) {	// L44
    drf_full[v37] = 0;	// L44
  }
  int32_t dsmask;	// L45
  dsmask = 0;	// L46
  int32_t crv_vld;	// L47
  crv_vld = 0;	// L48
  half crv_data;	// L49
  crv_data = (double)0.000000;	// L50
  int32_t crv_addr;	// L51
  crv_addr = 0;	// L52
  int32_t crv_mode;	// L53
  crv_mode = 0;	// L54
  int32_t crv_raw;	// L55
  crv_raw = 0;	// L56
  int32_t csd_vld;	// L57
  csd_vld = 0;	// L58
  ac_int<26, false> csd_pkt;	// L59
  csd_pkt = 0;	// L60
  int32_t csd_dir;	// L61
  csd_dir = 0;	// L62
  int32_t row_id;	// L63
  row_id = 0;	// L64
  int32_t col_id;	// L65
  col_id = 0;	// L66
  ac_int<26, false> oe_r;	// L67
  oe_r = 0;	// L68
  ac_int<26, false> ow_r;	// L69
  ow_r = 0;	// L70
  ac_int<26, false> on_r;	// L71
  on_r = 0;	// L72
  ac_int<26, false> os_r;	// L73
  os_r = 0;	// L74
  ac_int<17, false> txn_r;	// L75
  txn_r = 0;	// L76
  ac_int<17, false> txs_r;	// L77
  txs_r = 0;	// L78
  ac_int<17, false> txw_r;	// L79
  txw_r = 0;	// L80
  ac_int<17, false> txe_r;	// L81
  txe_r = 0;	// L82
  half hold_v[4][2];	// L83
  for (int v58 = 0; v58 < 4; v58++) {	// L84
    for (int v59 = 0; v59 < 2; v59++) {	// L84
      hold_v[v58][v59] = (double)0.000000;	// L84
    }
  }
  uint8_t hold_cnt[4];	// L85
  for (int v61 = 0; v61 < 4; v61++) {	// L86
    hold_cnt[v61] = 0;	// L86
  }
  ac_int<26, false> rbuf[4][2];	// L87
  for (int v63 = 0; v63 < 4; v63++) {	// L88
    for (int v64 = 0; v64 < 2; v64++) {	// L88
      rbuf[v63][v64] = 0;	// L88
    }
  }
  uint8_t rbcnt[4];	// L89
  for (int v66 = 0; v66 < 4; v66++) {	// L90
    rbcnt[v66] = 0;	// L90
  }
  uint8_t rcred[4];	// L91
  for (int v68 = 0; v68 < 4; v68++) {	// L92
    rcred[v68] = 0;	// L92
  }
  uint8_t cre_r;	// L93
  cre_r = 2;	// L94
  uint8_t crw_r;	// L95
  crw_r = 2;	// L96
  uint8_t crs_r;	// L97
  crs_r = 2;	// L98
  uint8_t crn_r;	// L99
  crn_r = 2;	// L100
  int32_t scred[4];	// L101
  for (int v74 = 0; v74 < 4; v74++) {	// L102
    scred[v74] = 0;	// L102
  }
  int32_t txp_v[4];	// L103
  for (int v76 = 0; v76 < 4; v76++) {	// L104
    txp_v[v76] = 0;	// L104
  }
  half txp_d[4];	// L105
  for (int v78 = 0; v78 < 4; v78++) {	// L106
    txp_d[v78] = (double)0.000000;	// L106
  }
  int32_t txp_r[4];	// L107
  for (int v80 = 0; v80 < 4; v80++) {	// L108
    txp_r[v80] = 0;	// L108
  }
  int32_t sc_r[4];	// L109
  for (int v82 = 0; v82 < 4; v82++) {	// L110
    sc_r[v82] = 2;	// L110
  }
  int32_t cfg_isz;	// L111
  cfg_isz = 0;	// L112
  int32_t cfg_itsz;	// L113
  cfg_itsz = 0;	// L114
  uint8_t fetch_en;	// L115
  fetch_en = 0;	// L116
  uint8_t instr_cnt;	// L117
  instr_cnt = 0;	// L118
  uint8_t iter_cnt;	// L119
  iter_cnt = 0;	// L120
  uint8_t condition_reg;	// L121
  condition_reg = 0;	// L122
  uint8_t sb_v[5];	// L123
  for (int v90 = 0; v90 < 5; v90++) {	// L124
    sb_v[v90] = 0;	// L124
  }
  uint8_t sb_dst[5];	// L125
  for (int v92 = 0; v92 < 5; v92++) {	// L126
    sb_dst[v92] = 0;	// L126
  }
  uint8_t sb_cmp[5];	// L127
  for (int v94 = 0; v94 < 5; v94++) {	// L128
    sb_cmp[v94] = 0;	// L128
  }
  uint8_t sb_rtr[5];	// L129
  for (int v96 = 0; v96 < 5; v96++) {	// L130
    sb_rtr[v96] = 0;	// L130
  }
  uint8_t sb_inj[5];	// L131
  for (int v98 = 0; v98 < 5; v98++) {	// L132
    sb_inj[v98] = 0;	// L132
  }
  uint8_t sb_dir[5];	// L133
  for (int v100 = 0; v100 < 5; v100++) {	// L134
    sb_dir[v100] = 0;	// L134
  }
  uint8_t sb_id[5];	// L135
  for (int v102 = 0; v102 < 5; v102++) {	// L136
    sb_id[v102] = 0;	// L136
  }
  uint8_t sb_rvld[5];	// L137
  for (int v104 = 0; v104 < 5; v104++) {	// L138
    sb_rvld[v104] = 0;	// L138
  }
  uint8_t sb_ix[5];	// L139
  for (int v106 = 0; v106 < 5; v106++) {	// L140
    sb_ix[v106] = 0;	// L140
  }
  uint8_t sb_long[5];	// L141
  for (int v108 = 0; v108 < 5; v108++) {	// L142
    sb_long[v108] = 0;	// L142
  }
  half resq[8];	// L143
  for (int v110 = 0; v110 < 8; v110++) {	// L144
    resq[v110] = (double)0.000000;	// L144
  }
  uint8_t cmpq[8];	// L145
  for (int v112 = 0; v112 < 8; v112++) {	// L146
    cmpq[v112] = 0;	// L146
  }
  uint8_t resq_wr;	// L147
  resq_wr = 0;	// L148
  ac_int<26, false> zpkt;	// L149
  zpkt = 0;	// L150
  ac_int<17, false> zsys;	// L151
  zsys = 0;	// L152
  int32_t zcr;	// L153
  zcr = 0;	// L154
  ac_int<26, true> v117 = zpkt;	// L155
  v0.write(v117);	// L156
  ac_int<26, true> v118 = zpkt;	// L157
  v1.write(v118);	// L158
  ac_int<26, true> v119 = zpkt;	// L159
  v2.write(v119);	// L160
  ac_int<26, true> v120 = zpkt;	// L161
  v3.write(v120);	// L162
  ac_int<17, true> v121 = zsys;	// L163
  v4.write(v121);	// L164
  ac_int<17, true> v122 = zsys;	// L165
  v5.write(v122);	// L166
  ac_int<17, true> v123 = zsys;	// L167
  v6.write(v123);	// L168
  ac_int<17, true> v124 = zsys;	// L169
  v7.write(v124);	// L170
  int32_t v125 = zcr;	// L171
  v8.write(v125);	// L172
  int32_t v126 = zcr;	// L173
  v9.write(v126);	// L174
  int32_t v127 = zcr;	// L175
  v10.write(v127);	// L176
  int32_t v128 = zcr;	// L177
  v11.write(v128);	// L178
  int32_t v129 = zcr;	// L179
  v12.write(v129);	// L180
  int32_t v130 = zcr;	// L181
  v13.write(v130);	// L182
  int32_t v131 = zcr;	// L183
  v14.write(v131);	// L184
  int32_t v132 = zcr;	// L185
  v15.write(v132);	// L186
  ac_int<26, true> v133 = zpkt;	// L187
  v0.write(v133);	// L188
  ac_int<26, true> v134 = zpkt;	// L189
  v1.write(v134);	// L190
  ac_int<26, true> v135 = zpkt;	// L191
  v2.write(v135);	// L192
  ac_int<26, true> v136 = zpkt;	// L193
  v3.write(v136);	// L194
  ac_int<17, true> v137 = zsys;	// L195
  v4.write(v137);	// L196
  ac_int<17, true> v138 = zsys;	// L197
  v5.write(v138);	// L198
  ac_int<17, true> v139 = zsys;	// L199
  v6.write(v139);	// L200
  ac_int<17, true> v140 = zsys;	// L201
  v7.write(v140);	// L202
  int32_t v141 = zcr;	// L203
  v8.write(v141);	// L204
  int32_t v142 = zcr;	// L205
  v9.write(v142);	// L206
  int32_t v143 = zcr;	// L207
  v10.write(v143);	// L208
  int32_t v144 = zcr;	// L209
  v11.write(v144);	// L210
  int32_t v145 = zcr;	// L211
  v12.write(v145);	// L212
  int32_t v146 = zcr;	// L213
  v13.write(v146);	// L214
  int32_t v147 = zcr;	// L215
  v14.write(v147);	// L216
  int32_t v148 = zcr;	// L217
  v15.write(v148);	// L218
  ac_int<26, true> v149 = zpkt;	// L219
  v0.write(v149);	// L220
  ac_int<26, true> v150 = zpkt;	// L221
  v1.write(v150);	// L222
  ac_int<26, true> v151 = zpkt;	// L223
  v2.write(v151);	// L224
  ac_int<26, true> v152 = zpkt;	// L225
  v3.write(v152);	// L226
  ac_int<17, true> v153 = zsys;	// L227
  v4.write(v153);	// L228
  ac_int<17, true> v154 = zsys;	// L229
  v5.write(v154);	// L230
  ac_int<17, true> v155 = zsys;	// L231
  v6.write(v155);	// L232
  ac_int<17, true> v156 = zsys;	// L233
  v7.write(v156);	// L234
  int32_t v157 = zcr;	// L235
  v8.write(v157);	// L236
  int32_t v158 = zcr;	// L237
  v9.write(v158);	// L238
  int32_t v159 = zcr;	// L239
  v10.write(v159);	// L240
  int32_t v160 = zcr;	// L241
  v11.write(v160);	// L242
  int32_t v161 = zcr;	// L243
  v12.write(v161);	// L244
  int32_t v162 = zcr;	// L245
  v13.write(v162);	// L246
  int32_t v163 = zcr;	// L247
  v14.write(v163);	// L248
  int32_t v164 = zcr;	// L249
  v15.write(v164);	// L250
  ac_int<26, true> v165 = zpkt;	// L251
  v0.write(v165);	// L252
  ac_int<26, true> v166 = zpkt;	// L253
  v1.write(v166);	// L254
  ac_int<26, true> v167 = zpkt;	// L255
  v2.write(v167);	// L256
  ac_int<26, true> v168 = zpkt;	// L257
  v3.write(v168);	// L258
  ac_int<17, true> v169 = zsys;	// L259
  v4.write(v169);	// L260
  ac_int<17, true> v170 = zsys;	// L261
  v5.write(v170);	// L262
  ac_int<17, true> v171 = zsys;	// L263
  v6.write(v171);	// L264
  ac_int<17, true> v172 = zsys;	// L265
  v7.write(v172);	// L266
  int32_t v173 = zcr;	// L267
  v8.write(v173);	// L268
  int32_t v174 = zcr;	// L269
  v9.write(v174);	// L270
  int32_t v175 = zcr;	// L271
  v10.write(v175);	// L272
  int32_t v176 = zcr;	// L273
  v11.write(v176);	// L274
  int32_t v177 = zcr;	// L275
  v12.write(v177);	// L276
  int32_t v178 = zcr;	// L277
  v13.write(v178);	// L278
  int32_t v179 = zcr;	// L279
  v14.write(v179);	// L280
  int32_t v180 = zcr;	// L281
  v15.write(v180);	// L282
  ac_int<26, true> v181 = zpkt;	// L283
  v0.write(v181);	// L284
  ac_int<26, true> v182 = zpkt;	// L285
  v1.write(v182);	// L286
  ac_int<26, true> v183 = zpkt;	// L287
  v2.write(v183);	// L288
  ac_int<26, true> v184 = zpkt;	// L289
  v3.write(v184);	// L290
  ac_int<17, true> v185 = zsys;	// L291
  v4.write(v185);	// L292
  ac_int<17, true> v186 = zsys;	// L293
  v5.write(v186);	// L294
  ac_int<17, true> v187 = zsys;	// L295
  v6.write(v187);	// L296
  ac_int<17, true> v188 = zsys;	// L297
  v7.write(v188);	// L298
  int32_t v189 = zcr;	// L299
  v8.write(v189);	// L300
  int32_t v190 = zcr;	// L301
  v9.write(v190);	// L302
  int32_t v191 = zcr;	// L303
  v10.write(v191);	// L304
  int32_t v192 = zcr;	// L305
  v11.write(v192);	// L306
  int32_t v193 = zcr;	// L307
  v12.write(v193);	// L308
  int32_t v194 = zcr;	// L309
  v13.write(v194);	// L310
  int32_t v195 = zcr;	// L311
  v14.write(v195);	// L312
  int32_t v196 = zcr;	// L313
  v15.write(v196);	// L314
  ac_int<26, true> v197 = oe_r;	// L315
  v0.write(v197);	// L316
  ac_int<26, true> v198 = ow_r;	// L317
  v1.write(v198);	// L318
  ac_int<26, true> v199 = os_r;	// L319
  v2.write(v199);	// L320
  ac_int<26, true> v200 = on_r;	// L321
  v3.write(v200);	// L322
  ac_int<17, true> v201 = txe_r;	// L323
  v4.write(v201);	// L324
  ac_int<17, true> v202 = txw_r;	// L325
  v5.write(v202);	// L326
  ac_int<17, true> v203 = txs_r;	// L327
  v6.write(v203);	// L328
  ac_int<17, true> v204 = txn_r;	// L329
  v7.write(v204);	// L330
  int8_t v205 = cre_r;	// L331
  v8.write(v205);	// L332
  int8_t v206 = crw_r;	// L333
  v9.write(v206);	// L334
  int8_t v207 = crs_r;	// L335
  v10.write(v207);	// L336
  int8_t v208 = crn_r;	// L337
  v11.write(v208);	// L338
  int32_t v209 = sc_r[0];	// L339
  v14.write(v209);	// L340
  int32_t v210 = sc_r[1];	// L341
  v15.write(v210);	// L342
  int32_t v211 = sc_r[2];	// L343
  v12.write(v211);	// L344
  int32_t v212 = sc_r[3];	// L345
  v13.write(v212);	// L346
  l_S_t_0_t: for (int t = 0; t < 10; t++) {	// L347
    ac_int<26, false> v214 = v16.read();	// L348
    ac_int<26, false> p_w;	// L349
    p_w = v214;	// L350
    ac_int<26, false> v216 = v17.read();	// L351
    ac_int<26, false> p_e;	// L352
    p_e = v216;	// L353
    ac_int<26, false> v218 = v18.read();	// L354
    ac_int<26, false> p_n;	// L355
    p_n = v218;	// L356
    ac_int<26, false> v220 = v19.read();	// L357
    ac_int<26, false> p_s;	// L358
    p_s = v220;	// L359
    int32_t v222 = v20.read();	// L360
    uint8_t v223 = rcred[0];	// L361
    ac_int<33, true> v224 = v223;	// L362
    ac_int<33, true> v225 = v222;	// L363
    ac_int<33, true> v226 = v224 + v225;	// L364
    uint8_t v227 = v226;	// L365
    rcred[0] = v227;	// L366
    int32_t v228 = v21.read();	// L367
    uint8_t v229 = rcred[1];	// L368
    ac_int<33, true> v230 = v229;	// L369
    ac_int<33, true> v231 = v228;	// L370
    ac_int<33, true> v232 = v230 + v231;	// L371
    uint8_t v233 = v232;	// L372
    rcred[1] = v233;	// L373
    int32_t v234 = v22.read();	// L374
    uint8_t v235 = rcred[2];	// L375
    ac_int<33, true> v236 = v235;	// L376
    ac_int<33, true> v237 = v234;	// L377
    ac_int<33, true> v238 = v236 + v237;	// L378
    uint8_t v239 = v238;	// L379
    rcred[2] = v239;	// L380
    int32_t v240 = v23.read();	// L381
    uint8_t v241 = rcred[3];	// L382
    ac_int<33, true> v242 = v241;	// L383
    ac_int<33, true> v243 = v240;	// L384
    ac_int<33, true> v244 = v242 + v243;	// L385
    uint8_t v245 = v244;	// L386
    rcred[3] = v245;	// L387
    int32_t v246 = v24.read();	// L388
    int32_t v247 = scred[0];	// L389
    ac_int<33, true> v248 = v247;	// L390
    ac_int<33, true> v249 = v246;	// L391
    ac_int<33, true> v250 = v248 + v249;	// L392
    int32_t v251 = v250;	// L393
    scred[0] = v251;	// L394
    int32_t v252 = v25.read();	// L395
    int32_t v253 = scred[1];	// L396
    ac_int<33, true> v254 = v253;	// L397
    ac_int<33, true> v255 = v252;	// L398
    ac_int<33, true> v256 = v254 + v255;	// L399
    int32_t v257 = v256;	// L400
    scred[1] = v257;	// L401
    int32_t v258 = v26.read();	// L402
    int32_t v259 = scred[2];	// L403
    ac_int<33, true> v260 = v259;	// L404
    ac_int<33, true> v261 = v258;	// L405
    ac_int<33, true> v262 = v260 + v261;	// L406
    int32_t v263 = v262;	// L407
    scred[2] = v263;	// L408
    int32_t v264 = v27.read();	// L409
    int32_t v265 = scred[3];	// L410
    ac_int<33, true> v266 = v265;	// L411
    ac_int<33, true> v267 = v264;	// L412
    ac_int<33, true> v268 = v266 + v267;	// L413
    int32_t v269 = v268;	// L414
    scred[3] = v269;	// L415
    ac_int<26, false> fin[4];	// L416
    for (int v271 = 0; v271 < 4; v271++) {	// L417
      fin[v271] = 0;	// L417
    }
    ac_int<26, true> v272 = p_w;	// L418
    fin[0] = v272;	// L419
    ac_int<26, true> v273 = p_e;	// L420
    fin[1] = v273;	// L421
    ac_int<26, true> v274 = p_n;	// L422
    fin[2] = v274;	// L423
    ac_int<26, true> v275 = p_s;	// L424
    fin[3] = v275;	// L425
    l_S_d_0_d: for (int d = 0; d < 4; d++) {	// L426
      ac_int<26, false> v277 = fin[d];	// L427
      bool v278;
      ap_int<26> v278_tmp = v277;
      v278 = v278_tmp[25];	// L428
      int32_t v279 = v278;	// L429
      bool v280 = v279 == 1;	// L430
      uint8_t v281 = rbcnt[d];	// L431
      int32_t v282 = v281;	// L432
      bool v283 = v282 < 2;	// L433
      bool v284 = v280 & v283;	// L434
      if (v284) {	// L435
        ac_int<26, false> v285 = fin[d];	// L436
        uint8_t v286 = rbcnt[d];	// L437
        int v287 = v286;	// L438
        rbuf[d][v287] = v285;	// L439
        uint8_t v288 = rbcnt[d];	// L440
        ac_int<33, true> v289 = v288;	// L441
        ac_int<33, true> v290 = v289 + 1;	// L442
        uint8_t v291 = v290;	// L443
        rbcnt[d] = v291;	// L444
      }
    }
    ac_int<26, false> hd[4];	// L447
    for (int v293 = 0; v293 < 4; v293++) {	// L448
      hd[v293] = 0;	// L448
    }
    int32_t hvld[4];	// L449
    for (int v295 = 0; v295 < 4; v295++) {	// L450
      hvld[v295] = 0;	// L450
    }
    int32_t hit[4];	// L451
    for (int v297 = 0; v297 < 4; v297++) {	// L452
      hit[v297] = 0;	// L452
    }
    int32_t axis[4];	// L453
    for (int v299 = 0; v299 < 4; v299++) {	// L454
      axis[v299] = 0;	// L454
    }
    int32_t v300 = col_id;	// L455
    axis[0] = v300;	// L456
    int32_t v301 = col_id;	// L457
    axis[1] = v301;	// L458
    int32_t v302 = row_id;	// L459
    axis[2] = v302;	// L460
    int32_t v303 = row_id;	// L461
    axis[3] = v303;	// L462
    l_S_d_1_d1: for (int d1 = 0; d1 < 4; d1++) {	// L463
      uint8_t v305 = rbcnt[d1];	// L464
      int32_t v306 = v305;	// L465
      bool v307 = v306 > 0;	// L466
      if (v307) {	// L467
        ac_int<26, false> v308 = rbuf[d1][0];	// L468
        hd[d1] = v308;	// L469
        hvld[d1] = 1;	// L470
        ac_int<26, false> v309 = hd[d1];	// L471
        ac_int<4, true> v310;
        ap_int<26> v310_tmp = v309;
        v310 = v310_tmp(24, 21);	// L472
        int32_t v311 = axis[d1];	// L473
        int32_t v312 = v310;	// L474
        bool v313 = v312 == v311;	// L475
        if (v313) {	// L476
          hit[d1] = 1;	// L477
        }
      }
    }
    ac_int<26, false> o_crv;	// L481
    o_crv = 0;	// L482
    int32_t crv_in;	// L483
    crv_in = -1;	// L484
    int32_t v316 = hit[3];	// L485
    bool v317 = v316 == 1;	// L486
    if (v317) {	// L487
      ac_int<26, false> v318 = hd[3];	// L488
      o_crv = v318;	// L489
      crv_in = 3;	// L490
    } else {
      int32_t v319 = hit[2];	// L492
      bool v320 = v319 == 1;	// L493
      if (v320) {	// L494
        ac_int<26, false> v321 = hd[2];	// L495
        o_crv = v321;	// L496
        crv_in = 2;	// L497
      } else {
        int32_t v322 = hit[1];	// L499
        bool v323 = v322 == 1;	// L500
        if (v323) {	// L501
          ac_int<26, false> v324 = hd[1];	// L502
          o_crv = v324;	// L503
          crv_in = 1;	// L504
        } else {
          int32_t v325 = hit[0];	// L506
          bool v326 = v325 == 1;	// L507
          if (v326) {	// L508
            ac_int<26, false> v327 = hd[0];	// L509
            o_crv = v327;	// L510
            crv_in = 0;	// L511
          }
        }
      }
    }
    ac_int<26, false> o_out[4];	// L516
    for (int v329 = 0; v329 < 4; v329++) {	// L517
      o_out[v329] = 0;	// L517
    }
    int32_t pop[4];	// L518
    for (int v331 = 0; v331 < 4; v331++) {	// L519
      pop[v331] = 0;	// L519
    }
    int32_t inj_done;	// L520
    inj_done = 0;	// L521
    int32_t idir;	// L522
    idir = -1;	// L523
    ac_int<26, true> v334 = csd_pkt;	// L524
    bool v335;
    ap_int<26> v335_tmp = v334;
    v335 = v335_tmp[25];	// L525
    int32_t v336 = v335;	// L526
    bool v337 = v336 == 1;	// L527
    if (v337) {	// L528
      int32_t v338 = csd_dir;	// L529
      ac_int<33, true> v339 = v338;	// L530
      ac_int<33, true> v340 = 3 - v339;	// L531
      int32_t v341 = v340;	// L532
      idir = v341;	// L533
    }
    l_S_o_2_o: for (int o = 0; o < 4; o++) {	// L535
      uint8_t v343 = rcred[o];	// L536
      int32_t v344 = v343;	// L537
      bool v345 = v344 > 0;	// L538
      if (v345) {	// L539
        int32_t v346 = idir;	// L540
        ac_int<33, true> v347 = v346;	// L541
        ac_int<33, true> v348 = o;	// L542
        bool v349 = v347 == v348;	// L543
        if (v349) {	// L544
          ac_int<26, true> v350 = csd_pkt;	// L545
          o_out[o] = v350;	// L546
          uint8_t v351 = rcred[o];	// L547
          ac_int<33, true> v352 = v351;	// L548
          ac_int<33, true> v353 = v352 - 1;	// L549
          uint8_t v354 = v353;	// L550
          rcred[o] = v354;	// L551
          inj_done = 1;	// L552
        } else {
          int32_t v355 = hvld[o];	// L554
          bool v356 = v355 == 1;	// L555
          int32_t v357 = hit[o];	// L556
          bool v358 = v357 == 0;	// L557
          bool v359 = v356 & v358;	// L558
          if (v359) {	// L559
            ac_int<26, false> v360 = hd[o];	// L560
            o_out[o] = v360;	// L561
            uint8_t v361 = rcred[o];	// L562
            ac_int<33, true> v362 = v361;	// L563
            ac_int<33, true> v363 = v362 - 1;	// L564
            uint8_t v364 = v363;	// L565
            rcred[o] = v364;	// L566
            pop[o] = 1;	// L567
          }
        }
      }
    }
    int32_t v365 = crv_in;	// L572
    bool v366 = v365 >= 0;	// L573
    if (v366) {	// L574
      int32_t v367 = crv_in;	// L575
      int v368 = v367;	// L576
      pop[v368] = 1;	// L577
    }
    int32_t ret[4];	// L579
    for (int v370 = 0; v370 < 4; v370++) {	// L580
      ret[v370] = 0;	// L580
    }
    l_S_d_3_d2: for (int d2 = 0; d2 < 4; d2++) {	// L581
      int32_t v372 = pop[d2];	// L582
      bool v373 = v372 == 1;	// L583
      if (v373) {	// L584
        l_S_sft_3_sft: for (int sft = 0; sft < 1; sft++) {	// L585
          ac_int<26, false> v375 = rbuf[d2][(sft + 1)];	// L586
          rbuf[d2][sft] = v375;	// L587
        }
        uint8_t v376 = rbcnt[d2];	// L589
        ac_int<33, true> v377 = v376;	// L590
        ac_int<33, true> v378 = v377 - 1;	// L591
        uint8_t v379 = v378;	// L592
        rbcnt[d2] = v379;	// L593
        ret[d2] = 1;	// L594
      }
    }
    int32_t v380 = ret[0];	// L597
    uint8_t v381 = v380;	// L598
    cre_r = v381;	// L599
    int32_t v382 = ret[1];	// L600
    uint8_t v383 = v382;	// L601
    crw_r = v383;	// L602
    int32_t v384 = ret[2];	// L603
    uint8_t v385 = v384;	// L604
    crs_r = v385;	// L605
    int32_t v386 = ret[3];	// L606
    uint8_t v387 = v386;	// L607
    crn_r = v387;	// L608
    ac_int<26, false> v388 = o_out[0];	// L609
    oe_r = v388;	// L610
    ac_int<26, false> v389 = o_out[1];	// L611
    ow_r = v389;	// L612
    ac_int<26, false> v390 = o_out[2];	// L613
    os_r = v390;	// L614
    ac_int<26, false> v391 = o_out[3];	// L615
    on_r = v391;	// L616
    int32_t v392 = inj_done;	// L617
    bool v393 = v392 == 1;	// L618
    if (v393) {	// L619
      csd_pkt = 0;	// L620
    }
    ac_int<26, true> v394 = o_crv;	// L622
    bool v395;
    ap_int<26> v395_tmp = v394;
    v395 = v395_tmp[25];	// L623
    int32_t v396 = v395;	// L624
    crv_vld = v396;	// L625
    ac_int<26, true> v397 = o_crv;	// L626
    int16_t v398;
    ap_int<26> v398_tmp = v397;
    v398 = v398_tmp(15, 0);	// L627
    half v399;
    union { uint16_t from; half to;} _converter_v398_to_v399 = {};
    _converter_v398_to_v399.from = v398;
    v399 = _converter_v398_to_v399.to;	// L628
    crv_data = v399;	// L629
    ac_int<26, true> v400 = o_crv;	// L630
    ac_int<4, true> v401;
    ap_int<26> v401_tmp = v400;
    v401 = v401_tmp(19, 16);	// L631
    int32_t v402 = v401;	// L632
    crv_addr = v402;	// L633
    ac_int<26, true> v403 = o_crv;	// L634
    bool v404;
    ap_int<26> v404_tmp = v403;
    v404 = v404_tmp[20];	// L635
    int32_t v405 = v404;	// L636
    crv_mode = v405;	// L637
    ac_int<26, true> v406 = o_crv;	// L638
    int16_t v407;
    ap_int<26> v407_tmp = v406;
    v407 = v407_tmp(15, 0);	// L639
    int32_t v408 = v407;	// L640
    crv_raw = v408;	// L641
    ac_int<17, false> v409 = v28.read();	// L642
    ac_int<17, false> rx_w;	// L643
    rx_w = v409;	// L644
    ac_int<17, false> v411 = v29.read();	// L645
    ac_int<17, false> rx_e;	// L646
    rx_e = v411;	// L647
    ac_int<17, false> v413 = v30.read();	// L648
    ac_int<17, false> rx_n;	// L649
    rx_n = v413;	// L650
    ac_int<17, false> v415 = v31.read();	// L651
    ac_int<17, false> rx_s;	// L652
    rx_s = v415;	// L653
    half rxv[4];	// L654
    for (int v418 = 0; v418 < 4; v418++) {	// L655
      rxv[v418] = (double)0.000000;	// L655
    }
    int32_t rxvld[4];	// L656
    for (int v420 = 0; v420 < 4; v420++) {	// L657
      rxvld[v420] = 0;	// L657
    }
    ac_int<17, true> v421 = rx_n;	// L658
    int16_t v422;
    ap_int<17> v422_tmp = v421;
    v422 = v422_tmp(16, 1);	// L659
    half v423;
    union { uint16_t from; half to;} _converter_v422_to_v423 = {};
    _converter_v422_to_v423.from = v422;
    v423 = _converter_v422_to_v423.to;	// L660
    rxv[0] = v423;	// L661
    ac_int<17, true> v424 = rx_n;	// L662
    bool v425;
    ap_int<17> v425_tmp = v424;
    v425 = v425_tmp[0];	// L663
    int32_t v426 = v425;	// L664
    rxvld[0] = v426;	// L665
    ac_int<17, true> v427 = rx_s;	// L666
    int16_t v428;
    ap_int<17> v428_tmp = v427;
    v428 = v428_tmp(16, 1);	// L667
    half v429;
    union { uint16_t from; half to;} _converter_v428_to_v429 = {};
    _converter_v428_to_v429.from = v428;
    v429 = _converter_v428_to_v429.to;	// L668
    rxv[1] = v429;	// L669
    ac_int<17, true> v430 = rx_s;	// L670
    bool v431;
    ap_int<17> v431_tmp = v430;
    v431 = v431_tmp[0];	// L671
    int32_t v432 = v431;	// L672
    rxvld[1] = v432;	// L673
    ac_int<17, true> v433 = rx_w;	// L674
    int16_t v434;
    ap_int<17> v434_tmp = v433;
    v434 = v434_tmp(16, 1);	// L675
    half v435;
    union { uint16_t from; half to;} _converter_v434_to_v435 = {};
    _converter_v434_to_v435.from = v434;
    v435 = _converter_v434_to_v435.to;	// L676
    rxv[2] = v435;	// L677
    ac_int<17, true> v436 = rx_w;	// L678
    bool v437;
    ap_int<17> v437_tmp = v436;
    v437 = v437_tmp[0];	// L679
    int32_t v438 = v437;	// L680
    rxvld[2] = v438;	// L681
    ac_int<17, true> v439 = rx_e;	// L682
    int16_t v440;
    ap_int<17> v440_tmp = v439;
    v440 = v440_tmp(16, 1);	// L683
    half v441;
    union { uint16_t from; half to;} _converter_v440_to_v441 = {};
    _converter_v440_to_v441.from = v440;
    v441 = _converter_v440_to_v441.to;	// L684
    rxv[3] = v441;	// L685
    ac_int<17, true> v442 = rx_e;	// L686
    bool v443;
    ap_int<17> v443_tmp = v442;
    v443 = v443_tmp[0];	// L687
    int32_t v444 = v443;	// L688
    rxvld[3] = v444;	// L689
    l_S_d_5_d3: for (int d3 = 0; d3 < 4; d3++) {	// L690
      int32_t v446 = rxvld[d3];	// L691
      bool v447 = v446 == 1;	// L692
      uint8_t v448 = hold_cnt[d3];	// L693
      int32_t v449 = v448;	// L694
      bool v450 = v449 < 2;	// L695
      bool v451 = v447 & v450;	// L696
      if (v451) {	// L697
        half v452 = rxv[d3];	// L698
        uint8_t v453 = hold_cnt[d3];	// L699
        int v454 = v453;	// L700
        hold_v[d3][v454] = v452;	// L701
        uint8_t v455 = hold_cnt[d3];	// L702
        ac_int<33, true> v456 = v455;	// L703
        ac_int<33, true> v457 = v456 + 1;	// L704
        uint8_t v458 = v457;	// L705
        hold_cnt[d3] = v458;	// L706
      }
    }
    int32_t retire_ok;	// L709
    retire_ok = 1;	// L710
    uint8_t v460 = sb_v[0];	// L711
    int32_t v461 = v460;	// L712
    bool v462 = v461 == 1;	// L713
    uint8_t v463 = sb_rtr[0];	// L714
    int32_t v464 = v463;	// L715
    bool v465 = v464 == 0;	// L716
    uint8_t v466 = sb_dst[0];	// L717
    int32_t v467 = v466;	// L718
    bool v468 = v467 >= 12;	// L719
    bool v469 = v462 & v465;	// L720
    bool v470 = v469 & v468;	// L721
    if (v470) {	// L722
      uint8_t v471 = sb_rvld[0];	// L723
      int32_t v472 = v471;	// L724
      bool v473 = v472 == 1;	// L725
      uint8_t v474 = sb_dst[0];	// L726
      int32_t v475 = v474;	// L727
      int32_t v476 = v475 & 3;	// L728
      int v477 = v476;	// L729
      int32_t v478 = txp_v[v477];	// L730
      bool v479 = v478 == 1;	// L731
      bool v480 = v473 & v479;	// L732
      if (v480) {	// L733
        retire_ok = 0;	// L734
      }
    }
    uint8_t v481 = sb_v[0];	// L737
    int32_t v482 = v481;	// L738
    bool v483 = v482 == 1;	// L739
    int32_t v484 = retire_ok;	// L740
    bool v485 = v484 == 1;	// L741
    bool v486 = v483 & v485;	// L742
    if (v486) {	// L743
      uint8_t v487 = sb_ix[0];	// L744
      int v488 = v487;	// L745
      half v489 = resq[v488];	// L746
      half wb;
#pragma HLS dependence variable=wb type=inter dependent=false	// L747
      wb = v489;	// L748
      uint8_t v491 = sb_cmp[0];	// L749
      int32_t v492 = v491;	// L750
      bool v493 = v492 == 1;	// L751
      if (v493) {	// L752
        uint8_t v494 = sb_ix[0];	// L753
        int v495 = v494;	// L754
        uint8_t v496 = cmpq[v495];	// L755
        condition_reg = v496;	// L756
      }
      uint8_t v497 = sb_rtr[0];	// L758
      int32_t v498 = v497;	// L759
      bool v499 = v498 == 1;	// L760
      if (v499) {	// L761
        uint8_t v500 = sb_inj[0];	// L762
        int32_t v501 = v500;	// L763
        bool v502 = v501 == 1;	// L764
        ac_int<26, true> v503 = csd_pkt;	// L765
        bool v504;
        ap_int<26> v504_tmp = v503;
        v504 = v504_tmp[25];	// L766
        int32_t v505 = v504;	// L767
        bool v506 = v505 == 0;	// L768
        bool v507 = v502 & v506;	// L769
        if (v507) {	// L770
          half v508 = wb;	// L771
          uint16_t v509;
          union { half from; uint16_t to;} _converter_v508_to_v509 = {};
          _converter_v508_to_v509.from = v508;
          v509 = _converter_v508_to_v509.to;	// L772
          ac_int<26, true> v510 = csd_pkt;	// L773
          ac_int<26, true> v511;
          ap_int<26> v511_tmp = v510;
          v511_tmp(15, 0) = v509;
          v511 = v511_tmp;	// L774
          csd_pkt = v511;	// L775
          uint8_t v512 = sb_dst[0];	// L776
          ac_int<4, false> v513 = v512;	// L777
          ac_int<26, true> v514 = csd_pkt;	// L778
          ac_int<26, true> v515;
          ap_int<26> v515_tmp = v514;
          v515_tmp(19, 16) = v513;
          v515 = v515_tmp;	// L779
          csd_pkt = v515;	// L780
          uint8_t v516 = sb_id[0];	// L781
          ac_int<4, false> v517 = v516;	// L782
          ac_int<26, true> v518 = csd_pkt;	// L783
          ac_int<26, true> v519;
          ap_int<26> v519_tmp = v518;
          v519_tmp(24, 21) = v517;
          v519 = v519_tmp;	// L784
          csd_pkt = v519;	// L785
          uint8_t v520 = sb_rvld[0];	// L786
          bool v521 = v520;	// L787
          ac_int<26, true> v522 = csd_pkt;	// L788
          ac_int<26, true> v523;
          ap_int<26> v523_tmp = v522;
          v523_tmp[25] = v521;          v523 = v523_tmp;	// L789
          csd_pkt = v523;	// L790
          uint8_t v524 = sb_dir[0];	// L791
          int32_t v525 = v524;	// L792
          csd_dir = v525;	// L793
        }
      } else {
        uint8_t v526 = sb_dst[0];	// L796
        int32_t v527 = v526;	// L797
        bool v528 = v527 >= 12;	// L798
        if (v528) {	// L799
          uint8_t v529 = sb_rvld[0];	// L800
          int32_t v530 = v529;	// L801
          bool v531 = v530 == 1;	// L802
          if (v531) {	// L803
            uint8_t v532 = sb_dst[0];	// L804
            int32_t v533 = v532;	// L805
            int32_t v534 = v533 & 3;	// L806
            int v535 = v534;	// L807
            txp_v[v535] = 1;	// L808
            half v536 = wb;	// L809
            uint8_t v537 = sb_dst[0];	// L810
            int32_t v538 = v537;	// L811
            int32_t v539 = v538 & 3;	// L812
            int v540 = v539;	// L813
            txp_d[v540] = v536;	// L814
            uint8_t v541 = sb_dst[0];	// L815
            int32_t v542 = v541;	// L816
            int32_t v543 = v542 & 3;	// L817
            int v544 = v543;	// L818
            txp_r[v544] = 1;	// L819
          }
        } else {
          uint8_t v545 = sb_rvld[0];	// L822
          int32_t v546 = v545;	// L823
          bool v547 = v546 == 1;	// L824
          if (v547) {	// L825
            uint8_t v548 = sb_dst[0];	// L826
            int32_t v549 = v548;	// L827
            bool v550 = v549 < 8;	// L828
            int32_t v551 = dsmask;	// L829
            int32_t v552 = v551 >> v549;	// L832
            int32_t v553 = v552 & 1;	// L833
            bool v554 = v553 == 1;	// L834
            bool v555 = v550 & v554;	// L835
            if (v555) {	// L836
              uint8_t v556 = sb_dst[0];	// L837
              int v557 = v556;	// L838
              int32_t v558 = drf_full[v557];	// L839
              bool v559 = v558 == 0;	// L840
              if (v559) {	// L841
                half v560 = wb;	// L842
                uint8_t v561 = sb_dst[0];	// L843
                int v562 = v561;	// L844
                drf[v562] = v560;	// L845
                uint8_t v563 = sb_dst[0];	// L846
                int v564 = v563;	// L847
                drf_full[v564] = 1;	// L848
              }
            } else {
              half v565 = wb;	// L851
              uint8_t v566 = sb_dst[0];	// L852
              int32_t v567 = v566;	// L853
              int32_t v568 = v567 & 7;	// L854
              int v569 = v568;	// L855
              drf[v569] = v565;	// L856
            }
          }
        }
      }
    }
    int32_t pc;	// L862
    pc = -1;	// L863
    int8_t v571 = fetch_en;	// L864
    int32_t v572 = v571;	// L865
    bool v573 = v572 == 1;	// L866
    if (v573) {	// L867
      int8_t v574 = instr_cnt;	// L868
      int32_t v575 = v574;	// L869
      pc = v575;	// L870
    }
    int32_t instr;	// L872
    instr = 0;	// L873
    int32_t v577 = pc;	// L874
    bool v578 = v577 >= 0;	// L875
    if (v578) {	// L876
      int32_t v579 = pc;	// L877
      int v580 = v579;	// L878
      int32_t v581 = irf[v580];	// L879
      instr = v581;	// L880
    }
    int32_t v582 = instr;	// L882
    int32_t v583 = v582 & 15;	// L883
    int32_t op;	// L884
    op = v583;	// L885
    int32_t v585 = instr;	// L886
    int32_t v586 = v585 >> 4;	// L887
    int32_t v587 = v586 & 15;	// L888
    int32_t dst;	// L889
    dst = v587;	// L890
    int32_t v589 = instr;	// L891
    int32_t v590 = v589 >> 8;	// L892
    int32_t v591 = v590 & 15;	// L893
    int32_t s1;	// L894
    s1 = v591;	// L895
    int32_t v593 = instr;	// L896
    int32_t v594 = v593 >> 12;	// L897
    int32_t v595 = v594 & 15;	// L898
    int32_t s2;	// L899
    s2 = v595;	// L900
    half a;	// L901
    a = (double)0.000000;	// L902
    half b;	// L903
    b = (double)0.000000;	// L904
    int32_t v599 = s1;	// L905
    bool v600 = v599 >= 12;	// L906
    if (v600) {	// L907
      int32_t v601 = s1;	// L908
      int32_t v602 = v601 & 3;	// L909
      int v603 = v602;	// L910
      half v604 = hold_v[v603][0];	// L911
      a = v604;	// L912
    } else {
      int32_t v605 = s1;	// L914
      int v606 = v605;	// L915
      half v607 = drf[v606];	// L916
      a = v607;	// L917
    }
    int32_t v608 = s2;	// L919
    bool v609 = v608 >= 12;	// L920
    if (v609) {	// L921
      int32_t v610 = s2;	// L922
      int32_t v611 = v610 & 3;	// L923
      int v612 = v611;	// L924
      half v613 = hold_v[v612][0];	// L925
      b = v613;	// L926
    } else {
      int32_t v614 = s2;	// L928
      int v615 = v614;	// L929
      half v616 = drf[v615];	// L930
      b = v616;	// L931
    }
    int32_t a_vld;	// L933
    a_vld = 1;	// L934
    int32_t b_vld;	// L935
    b_vld = 1;	// L936
    int32_t v619 = s1;	// L937
    bool v620 = v619 >= 12;	// L938
    if (v620) {	// L939
      a_vld = 0;	// L940
      int32_t v621 = s1;	// L941
      int32_t v622 = v621 & 3;	// L942
      int v623 = v622;	// L943
      uint8_t v624 = hold_cnt[v623];	// L944
      int32_t v625 = v624;	// L945
      bool v626 = v625 > 0;	// L946
      if (v626) {	// L947
        a_vld = 1;	// L948
      }
    }
    int32_t v627 = s2;	// L951
    bool v628 = v627 >= 12;	// L952
    if (v628) {	// L953
      b_vld = 0;	// L954
      int32_t v629 = s2;	// L955
      int32_t v630 = v629 & 3;	// L956
      int v631 = v630;	// L957
      uint8_t v632 = hold_cnt[v631];	// L958
      int32_t v633 = v632;	// L959
      bool v634 = v633 > 0;	// L960
      if (v634) {	// L961
        b_vld = 1;	// L962
      }
    }
    int32_t v635 = s1;	// L965
    bool v636 = v635 < 8;	// L966
    int32_t v637 = dsmask;	// L967
    int32_t v638 = v637 >> v635;	// L969
    int32_t v639 = v638 & 1;	// L970
    bool v640 = v639 == 1;	// L971
    bool v641 = v636 & v640;	// L972
    if (v641) {	// L973
      int32_t v642 = s1;	// L974
      int v643 = v642;	// L975
      int32_t v644 = drf_full[v643];	// L976
      bool v645 = v644 == 0;	// L977
      if (v645) {	// L978
        a_vld = 0;	// L979
      }
    }
    int32_t v646 = s2;	// L982
    bool v647 = v646 < 8;	// L983
    int32_t v648 = dsmask;	// L984
    int32_t v649 = v648 >> v646;	// L986
    int32_t v650 = v649 & 1;	// L987
    bool v651 = v650 == 1;	// L988
    bool v652 = v647 & v651;	// L989
    if (v652) {	// L990
      int32_t v653 = s2;	// L991
      int v654 = v653;	// L992
      int32_t v655 = drf_full[v654];	// L993
      bool v656 = v655 == 0;	// L994
      if (v656) {	// L995
        b_vld = 0;	// L996
      }
    }
    int32_t binop;	// L999
    binop = 0;	// L1000
    int32_t v658 = op;	// L1001
    bool v659 = v658 == 0;	// L1002
    bool v660 = v658 == 1;	// L1004
    bool v661 = v658 == 2;	// L1006
    bool v662 = v658 == 8;	// L1008
    bool v663 = v658 == 9;	// L1010
    bool v664 = v659 | v660;	// L1011
    bool v665 = v664 | v661;	// L1012
    bool v666 = v665 | v662;	// L1013
    bool v667 = v666 | v663;	// L1014
    if (v667) {	// L1015
      binop = 1;	// L1016
    }
    int32_t raw;	// L1018
    raw = 0;	// L1019
    int32_t cmp_busy;	// L1020
    cmp_busy = 0;	// L1021
    int32_t fwd_a;	// L1022
    fwd_a = 0;	// L1023
    int32_t fwd_a_ix;	// L1024
    fwd_a_ix = 0;	// L1025
    int32_t raw_a;	// L1026
    raw_a = 0;	// L1027
    int32_t fwd_b;	// L1028
    fwd_b = 0;	// L1029
    int32_t fwd_b_ix;	// L1030
    fwd_b_ix = 0;	// L1031
    int32_t raw_b;	// L1032
    raw_b = 0;	// L1033
    l_S_k_6_k: for (int k = 0; k < 4; k++) {	// L1034
      ac_int<34, true> v677 = k;	// L1035
      ac_int<34, true> v678 = v677 + 1;	// L1036
      int32_t v679 = v678;	// L1037
      int32_t kk;	// L1038
      kk = v679;	// L1039
      int32_t v681 = kk;	// L1040
      ac_int<34, true> v682 = v681;	// L1041
      ac_int<34, true> v683 = 4 - v682;	// L1042
      int32_t v684 = v683;	// L1043
      int32_t inflight;	// L1044
      inflight = v684;	// L1045
      int32_t need;	// L1046
      need = 0;	// L1047
      int32_t v687 = kk;	// L1048
      int v688 = v687;	// L1049
      uint8_t v689 = sb_long[v688];	// L1050
      int32_t v690 = v689;	// L1051
      bool v691 = v690 == 1;	// L1052
      if (v691) {	// L1053
        need = 1;	// L1054
      }
      int32_t rdy;	// L1056
      rdy = 0;	// L1057
      int32_t v693 = inflight;	// L1058
      int32_t v694 = need;	// L1059
      bool v695 = v693 >= v694;	// L1060
      if (v695) {	// L1061
        rdy = 1;	// L1062
      }
      int32_t v696 = kk;	// L1064
      int v697 = v696;	// L1065
      uint8_t v698 = sb_v[v697];	// L1066
      int32_t v699 = v698;	// L1067
      bool v700 = v699 == 1;	// L1068
      uint8_t v701 = sb_rtr[v697];	// L1071
      int32_t v702 = v701;	// L1072
      bool v703 = v702 == 0;	// L1073
      uint8_t v704 = sb_dst[v697];	// L1076
      int32_t v705 = v704;	// L1077
      bool v706 = v705 < 12;	// L1078
      bool v707 = v700 & v703;	// L1079
      bool v708 = v707 & v706;	// L1080
      if (v708) {	// L1081
        int32_t v709 = s1;	// L1082
        bool v710 = v709 < 12;	// L1083
        int32_t v711 = kk;	// L1084
        int v712 = v711;	// L1085
        uint8_t v713 = sb_dst[v712];	// L1086
        int32_t v714 = v713;	// L1087
        int32_t v715 = v714 & 7;	// L1088
        int32_t v716 = v709 & 7;	// L1090
        bool v717 = v715 == v716;	// L1091
        bool v718 = v710 & v717;	// L1092
        if (v718) {	// L1093
          int32_t v719 = rdy;	// L1094
          bool v720 = v719 == 1;	// L1095
          if (v720) {	// L1096
            fwd_a = 1;	// L1097
            int32_t v721 = kk;	// L1098
            int v722 = v721;	// L1099
            uint8_t v723 = sb_ix[v722];	// L1100
            int32_t v724 = v723;	// L1101
            fwd_a_ix = v724;	// L1102
            raw_a = 0;	// L1103
          } else {
            fwd_a = 0;	// L1105
            raw_a = 1;	// L1106
          }
        }
        int32_t v725 = binop;	// L1109
        bool v726 = v725 == 1;	// L1110
        int32_t v727 = s2;	// L1111
        bool v728 = v727 < 12;	// L1112
        int32_t v729 = kk;	// L1113
        int v730 = v729;	// L1114
        uint8_t v731 = sb_dst[v730];	// L1115
        int32_t v732 = v731;	// L1116
        int32_t v733 = v732 & 7;	// L1117
        int32_t v734 = v727 & 7;	// L1119
        bool v735 = v733 == v734;	// L1120
        bool v736 = v726 & v728;	// L1121
        bool v737 = v736 & v735;	// L1122
        if (v737) {	// L1123
          int32_t v738 = rdy;	// L1124
          bool v739 = v738 == 1;	// L1125
          if (v739) {	// L1126
            fwd_b = 1;	// L1127
            int32_t v740 = kk;	// L1128
            int v741 = v740;	// L1129
            uint8_t v742 = sb_ix[v741];	// L1130
            int32_t v743 = v742;	// L1131
            fwd_b_ix = v743;	// L1132
            raw_b = 0;	// L1133
          } else {
            fwd_b = 0;	// L1135
            raw_b = 1;	// L1136
          }
        }
      }
      int32_t v744 = kk;	// L1140
      int v745 = v744;	// L1141
      uint8_t v746 = sb_v[v745];	// L1142
      int32_t v747 = v746;	// L1143
      bool v748 = v747 == 1;	// L1144
      uint8_t v749 = sb_cmp[v745];	// L1147
      int32_t v750 = v749;	// L1148
      bool v751 = v750 == 1;	// L1149
      bool v752 = v748 & v751;	// L1150
      if (v752) {	// L1151
        cmp_busy = 1;	// L1152
      }
    }
    int32_t v753 = raw_a;	// L1155
    raw = v753;	// L1156
    int32_t v754 = binop;	// L1157
    bool v755 = v754 == 1;	// L1158
    int32_t v756 = raw_b;	// L1159
    bool v757 = v756 == 1;	// L1160
    bool v758 = v755 & v757;	// L1161
    if (v758) {	// L1162
      raw = 1;	// L1163
    }
    int32_t v759 = fwd_a;	// L1165
    bool v760 = v759 == 1;	// L1166
    if (v760) {	// L1167
      int32_t v761 = fwd_a_ix;	// L1168
      int v762 = v761;	// L1169
      half v763 = resq[v762];	// L1170
      a = v763;	// L1171
      a_vld = 1;	// L1172
    }
    int32_t v764 = fwd_b;	// L1174
    bool v765 = v764 == 1;	// L1175
    if (v765) {	// L1176
      int32_t v766 = fwd_b_ix;	// L1177
      int v767 = v766;	// L1178
      half v768 = resq[v767];	// L1179
      b = v768;	// L1180
      b_vld = 1;	// L1181
    }
    int32_t is_cond;	// L1183
    is_cond = 0;	// L1184
    int32_t v770 = op;	// L1185
    bool v771 = v770 >= 12;	// L1186
    ac_int<33, true> v772 = v770;	// L1188
    bool v773 = v772 <= 15;	// L1189
    bool v774 = v771 & v773;	// L1190
    if (v774) {	// L1191
      is_cond = 1;	// L1192
    }
    int32_t grant;	// L1194
    grant = 0;	// L1195
    int32_t v776 = pc;	// L1196
    bool v777 = v776 >= 0;	// L1197
    if (v777) {	// L1198
      grant = 1;	// L1199
    }
    int32_t v778 = pc;	// L1201
    bool v779 = v778 >= 0;	// L1202
    int32_t v780 = a_vld;	// L1203
    bool v781 = v780 == 0;	// L1204
    int32_t v782 = binop;	// L1205
    bool v783 = v782 == 1;	// L1206
    int32_t v784 = b_vld;	// L1207
    bool v785 = v784 == 0;	// L1208
    bool v786 = v783 & v785;	// L1209
    bool v787 = v781 | v786;	// L1210
    bool v788 = v779 & v787;	// L1211
    if (v788) {	// L1212
      grant = 0;	// L1213
    }
    int32_t v789 = pc;	// L1215
    bool v790 = v789 >= 0;	// L1216
    int32_t v791 = raw;	// L1217
    bool v792 = v791 == 1;	// L1218
    int32_t v793 = is_cond;	// L1219
    bool v794 = v793 == 1;	// L1220
    int32_t v795 = cmp_busy;	// L1221
    bool v796 = v795 == 1;	// L1222
    bool v797 = v794 & v796;	// L1223
    bool v798 = v792 | v797;	// L1224
    bool v799 = v790 & v798;	// L1225
    if (v799) {	// L1226
      grant = 0;	// L1227
    }
    int32_t v800 = retire_ok;	// L1229
    bool v801 = v800 == 0;	// L1230
    if (v801) {	// L1231
      grant = 0;	// L1232
    }
    int32_t v802 = grant;	// L1234
    bool v803 = v802 == 1;	// L1235
    if (v803) {	// L1236
      int8_t v804 = instr_cnt;	// L1237
      int32_t v805 = cfg_isz;	// L1238
      int32_t v806 = v804;	// L1239
      bool v807 = v806 == v805;	// L1240
      if (v807) {	// L1241
        instr_cnt = 0;	// L1242
        int8_t v808 = iter_cnt;	// L1243
        int32_t v809 = cfg_itsz;	// L1244
        ac_int<33, true> v810 = v809;	// L1245
        ac_int<33, true> v811 = v810 - 1;	// L1246
        ac_int<33, true> v812 = v808;	// L1247
        bool v813 = v812 == v811;	// L1248
        if (v813) {	// L1249
          fetch_en = 0;	// L1250
        } else {
          int8_t v814 = iter_cnt;	// L1252
          ac_int<33, true> v815 = v814;	// L1253
          ac_int<33, true> v816 = v815 + 1;	// L1254
          uint8_t v817 = v816;	// L1255
          iter_cnt = v817;	// L1256
        }
      } else {
        int8_t v818 = instr_cnt;	// L1259
        ac_int<33, true> v819 = v818;	// L1260
        ac_int<33, true> v820 = v819 + 1;	// L1261
        uint8_t v821 = v820;	// L1262
        instr_cnt = v821;	// L1263
      }
    }
    int32_t c1;	// L1266
    c1 = -1;	// L1267
    int32_t c2;	// L1268
    c2 = -1;	// L1269
    int32_t v824 = grant;	// L1270
    bool v825 = v824 == 1;	// L1271
    int32_t v826 = s1;	// L1272
    bool v827 = v826 >= 12;	// L1273
    bool v828 = v825 & v827;	// L1274
    if (v828) {	// L1275
      int32_t v829 = s1;	// L1276
      int32_t v830 = v829 & 3;	// L1277
      c1 = v830;	// L1278
    }
    int32_t v831 = grant;	// L1280
    bool v832 = v831 == 1;	// L1281
    int32_t v833 = s2;	// L1282
    bool v834 = v833 >= 12;	// L1283
    bool v835 = v832 & v834;	// L1284
    if (v835) {	// L1285
      int32_t v836 = s2;	// L1286
      int32_t v837 = v836 & 3;	// L1287
      c2 = v837;	// L1288
    }
    int32_t v838 = c1;	// L1290
    bool v839 = v838 >= 0;	// L1291
    if (v839) {	// L1292
      int32_t v840 = c1;	// L1293
      int v841 = v840;	// L1294
      half v842 = hold_v[v841][1];	// L1295
      hold_v[v841][0] = v842;	// L1298
      int32_t v843 = c1;	// L1299
      int v844 = v843;	// L1300
      uint8_t v845 = hold_cnt[v844];	// L1301
      ac_int<33, true> v846 = v845;	// L1302
      ac_int<33, true> v847 = v846 - 1;	// L1303
      uint8_t v848 = v847;	// L1304
      hold_cnt[v844] = v848;	// L1307
    }
    int32_t v849 = c2;	// L1309
    bool v850 = v849 >= 0;	// L1310
    int32_t v851 = c1;	// L1312
    bool v852 = v849 != v851;	// L1313
    bool v853 = v850 & v852;	// L1314
    if (v853) {	// L1315
      int32_t v854 = c2;	// L1316
      int v855 = v854;	// L1317
      half v856 = hold_v[v855][1];	// L1318
      hold_v[v855][0] = v856;	// L1321
      int32_t v857 = c2;	// L1322
      int v858 = v857;	// L1323
      uint8_t v859 = hold_cnt[v858];	// L1324
      ac_int<33, true> v860 = v859;	// L1325
      ac_int<33, true> v861 = v860 - 1;	// L1326
      uint8_t v862 = v861;	// L1327
      hold_cnt[v858] = v862;	// L1330
    }
    l_S_d_7_d4: for (int d4 = 0; d4 < 4; d4++) {	// L1332
      sc_r[d4] = 0;	// L1333
    }
    int32_t v864 = c1;	// L1335
    bool v865 = v864 >= 0;	// L1336
    if (v865) {	// L1337
      int32_t v866 = c1;	// L1338
      int v867 = v866;	// L1339
      sc_r[v867] = 1;	// L1340
    }
    int32_t v868 = c2;	// L1342
    bool v869 = v868 >= 0;	// L1343
    int32_t v870 = c1;	// L1345
    bool v871 = v868 != v870;	// L1346
    bool v872 = v869 & v871;	// L1347
    if (v872) {	// L1348
      int32_t v873 = c2;	// L1349
      int v874 = v873;	// L1350
      sc_r[v874] = 1;	// L1351
    }
    int32_t v875 = grant;	// L1353
    bool v876 = v875 == 1;	// L1354
    int32_t v877 = s1;	// L1355
    bool v878 = v877 < 8;	// L1356
    int32_t v879 = dsmask;	// L1357
    int32_t v880 = v879 >> v877;	// L1359
    int32_t v881 = v880 & 1;	// L1360
    bool v882 = v881 == 1;	// L1361
    bool v883 = v876 & v878;	// L1362
    bool v884 = v883 & v882;	// L1363
    if (v884) {	// L1364
      int32_t v885 = s1;	// L1365
      int v886 = v885;	// L1366
      drf_full[v886] = 0;	// L1367
    }
    int32_t v887 = grant;	// L1369
    bool v888 = v887 == 1;	// L1370
    int32_t v889 = s2;	// L1371
    bool v890 = v889 < 8;	// L1372
    int32_t v891 = dsmask;	// L1373
    int32_t v892 = v891 >> v889;	// L1375
    int32_t v893 = v892 & 1;	// L1376
    bool v894 = v893 == 1;	// L1377
    bool v895 = v888 & v890;	// L1378
    bool v896 = v895 & v894;	// L1379
    if (v896) {	// L1380
      int32_t v897 = s2;	// L1381
      int v898 = v897;	// L1382
      drf_full[v898] = 0;	// L1383
    }
    half res;
#pragma HLS dependence variable=res type=inter dependent=false	// L1385
    res = (double)0.000000;	// L1386
    int32_t v900 = op;	// L1387
    bool v901 = v900 == 0;	// L1388
    if (v901) {	// L1389
      half v902 = a;	// L1390
      half v903 = b;	// L1391
      half v904 = v902 + v903;	// L1392
      res = v904;	// L1393
    } else {
      int32_t v905 = op;	// L1395
      bool v906 = v905 == 1;	// L1396
      if (v906) {	// L1397
        half v907 = a;	// L1398
        half v908 = b;	// L1399
        half v909 = v907 - v908;	// L1400
        res = v909;	// L1401
      } else {
        int32_t v910 = op;	// L1403
        bool v911 = v910 == 2;	// L1404
        if (v911) {	// L1405
          half v912 = a;	// L1406
          half v913 = b;	// L1407
          half v914 = v912 * v913;	// L1408
          res = v914;	// L1409
        } else {
          int32_t v915 = op;	// L1411
          bool v916 = v915 == 8;	// L1412
          if (v916) {	// L1413
            half v917 = a;	// L1414
            half v918 = b;	// L1415
            bool v919 = v917 >= v918;	// L1416
            if (v919) {	// L1417
              res = (double)1.000000;	// L1418
            } else {
              res = (double)-1.000000;	// L1420
            }
          } else {
            int32_t v920 = op;	// L1423
            bool v921 = v920 == 9;	// L1424
            if (v921) {	// L1425
              half v922 = a;	// L1426
              half v923 = b;	// L1427
              bool v924 = v922 < v923;	// L1428
              if (v924) {	// L1429
                res = (double)1.000000;	// L1430
              } else {
                res = (double)-1.000000;	// L1432
              }
            } else {
              half v925 = a;	// L1435
              res = v925;	// L1436
            }
          }
        }
      }
    }
    int32_t v926 = a_vld;	// L1442
    int32_t res_vld;	// L1443
    res_vld = v926;	// L1444
    int32_t v928 = op;	// L1445
    bool v929 = v928 == 0;	// L1446
    bool v930 = v928 == 1;	// L1448
    bool v931 = v928 == 2;	// L1450
    bool v932 = v928 == 8;	// L1452
    bool v933 = v928 == 9;	// L1454
    bool v934 = v929 | v930;	// L1455
    bool v935 = v934 | v931;	// L1456
    bool v936 = v935 | v932;	// L1457
    bool v937 = v936 | v933;	// L1458
    if (v937) {	// L1459
      int32_t v938 = a_vld;	// L1460
      int32_t v939 = b_vld;	// L1461
      int64_t v940 = v938;	// L1462
      int64_t v941 = v939;	// L1463
      int64_t v942 = v940 * v941;	// L1464
      int32_t v943 = v942;	// L1465
      res_vld = v943;	// L1466
    }
    int32_t v944 = grant;	// L1468
    bool v945 = v944 == 0;	// L1469
    if (v945) {	// L1470
      res_vld = 0;	// L1471
    }
    int32_t is_rtr;	// L1473
    is_rtr = 0;	// L1474
    int32_t v947 = op;	// L1475
    bool v948 = v947 >= 4;	// L1476
    ac_int<33, true> v949 = v947;	// L1478
    bool v950 = v949 <= 7;	// L1479
    bool v951 = v948 & v950;	// L1480
    if (v951) {	// L1481
      is_rtr = 1;	// L1482
    }
    int32_t v952 = retire_ok;	// L1484
    bool v953 = v952 == 1;	// L1485
    if (v953) {	// L1486
      l_S_k_8_k1: for (int k1 = 0; k1 < 4; k1++) {	// L1487
        uint8_t v955 = sb_v[(k1 + 1)];	// L1488
        sb_v[k1] = v955;	// L1489
        uint8_t v956 = sb_dst[(k1 + 1)];	// L1490
        sb_dst[k1] = v956;	// L1491
        uint8_t v957 = sb_cmp[(k1 + 1)];	// L1492
        sb_cmp[k1] = v957;	// L1493
        uint8_t v958 = sb_rtr[(k1 + 1)];	// L1494
        sb_rtr[k1] = v958;	// L1495
        uint8_t v959 = sb_inj[(k1 + 1)];	// L1496
        sb_inj[k1] = v959;	// L1497
        uint8_t v960 = sb_dir[(k1 + 1)];	// L1498
        sb_dir[k1] = v960;	// L1499
        uint8_t v961 = sb_id[(k1 + 1)];	// L1500
        sb_id[k1] = v961;	// L1501
        uint8_t v962 = sb_rvld[(k1 + 1)];	// L1502
        sb_rvld[k1] = v962;	// L1503
        uint8_t v963 = sb_ix[(k1 + 1)];	// L1504
        sb_ix[k1] = v963;	// L1505
        uint8_t v964 = sb_long[(k1 + 1)];	// L1506
        sb_long[k1] = v964;	// L1507
      }
      sb_v[4] = 0;	// L1509
    }
    int32_t v965 = grant;	// L1511
    bool v966 = v965 == 1;	// L1512
    if (v966) {	// L1513
      half v967 = res;	// L1514
      int8_t v968 = resq_wr;	// L1515
      int v969 = v968;	// L1516
      resq[v969] = v967;	// L1517
      int32_t cq;	// L1518
      cq = 0;	// L1519
      int32_t v971 = op;	// L1520
      bool v972 = v971 == 8;	// L1521
      if (v972) {	// L1522
        half v973 = a;	// L1523
        half v974 = b;	// L1524
        bool v975 = v973 >= v974;	// L1525
        if (v975) {	// L1526
          cq = 1;	// L1527
        }
      }
      int32_t v976 = op;	// L1530
      bool v977 = v976 == 9;	// L1531
      if (v977) {	// L1532
        half v978 = a;	// L1533
        half v979 = b;	// L1534
        bool v980 = v978 < v979;	// L1535
        if (v980) {	// L1536
          cq = 1;	// L1537
        }
      }
      int32_t v981 = cq;	// L1540
      uint8_t v982 = v981;	// L1541
      int8_t v983 = resq_wr;	// L1542
      int v984 = v983;	// L1543
      cmpq[v984] = v982;	// L1544
      sb_v[4] = 1;	// L1545
      int32_t v985 = dst;	// L1546
      uint8_t v986 = v985;	// L1547
      sb_dst[4] = v986;	// L1548
      int8_t v987 = resq_wr;	// L1549
      sb_ix[4] = v987;	// L1550
      int32_t v988 = binop;	// L1551
      uint8_t v989 = v988;	// L1552
      sb_long[4] = v989;	// L1553
      sb_cmp[4] = 0;	// L1554
      int32_t v990 = op;	// L1555
      bool v991 = v990 == 8;	// L1556
      bool v992 = v990 == 9;	// L1558
      bool v993 = v991 | v992;	// L1559
      if (v993) {	// L1560
        sb_cmp[4] = 1;	// L1561
      }
      int32_t v994 = is_rtr;	// L1563
      int32_t rtrf;	// L1564
      rtrf = v994;	// L1565
      int32_t v996 = is_cond;	// L1566
      bool v997 = v996 == 1;	// L1567
      if (v997) {	// L1568
        rtrf = 1;	// L1569
      }
      int32_t v998 = rtrf;	// L1571
      uint8_t v999 = v998;	// L1572
      sb_rtr[4] = v999;	// L1573
      int32_t v1000 = is_rtr;	// L1574
      int32_t inj;	// L1575
      inj = v1000;	// L1576
      int32_t v1002 = is_cond;	// L1577
      bool v1003 = v1002 == 1;	// L1578
      int8_t v1004 = condition_reg;	// L1579
      int32_t v1005 = v1004;	// L1580
      bool v1006 = v1005 == 1;	// L1581
      bool v1007 = v1003 & v1006;	// L1582
      if (v1007) {	// L1583
        inj = 1;	// L1584
      }
      int32_t v1008 = inj;	// L1586
      uint8_t v1009 = v1008;	// L1587
      sb_inj[4] = v1009;	// L1588
      int32_t v1010 = op;	// L1589
      int32_t v1011 = v1010 & 3;	// L1590
      uint8_t v1012 = v1011;	// L1591
      sb_dir[4] = v1012;	// L1592
      int32_t v1013 = s2;	// L1593
      uint8_t v1014 = v1013;	// L1594
      sb_id[4] = v1014;	// L1595
      int32_t v1015 = res_vld;	// L1596
      uint8_t v1016 = v1015;	// L1597
      sb_rvld[4] = v1016;	// L1598
      int8_t v1017 = resq_wr;	// L1599
      ac_int<33, true> v1018 = v1017;	// L1600
      ac_int<33, true> v1019 = v1018 + 1;	// L1601
      ac_int<33, true> v1020 = v1019 & 7;	// L1602
      uint8_t v1021 = v1020;	// L1603
      resq_wr = v1021;	// L1604
    }
    txn_r = 0;	// L1606
    txs_r = 0;	// L1607
    txw_r = 0;	// L1608
    txe_r = 0;	// L1609
    int32_t v1022 = txp_v[0];	// L1610
    bool v1023 = v1022 == 1;	// L1611
    int32_t v1024 = scred[0];	// L1612
    bool v1025 = v1024 > 0;	// L1613
    bool v1026 = v1023 & v1025;	// L1614
    if (v1026) {	// L1615
      ac_int<17, false> twn;	// L1616
      twn = 0;	// L1617
      ac_int<17, true> v1028 = twn;	// L1618
      ac_int<17, true> v1029;
      ap_int<17> v1029_tmp = v1028;
      v1029_tmp[0] = 1;      v1029 = v1029_tmp;	// L1619
      twn = v1029;	// L1620
      half v1030 = txp_d[0];	// L1621
      uint16_t v1031;
      union { half from; uint16_t to;} _converter_v1030_to_v1031 = {};
      _converter_v1030_to_v1031.from = v1030;
      v1031 = _converter_v1030_to_v1031.to;	// L1622
      ac_int<17, true> v1032 = twn;	// L1623
      ac_int<17, true> v1033;
      ap_int<17> v1033_tmp = v1032;
      v1033_tmp(16, 1) = v1031;
      v1033 = v1033_tmp;	// L1624
      twn = v1033;	// L1625
      ac_int<17, true> v1034 = twn;	// L1626
      txn_r = v1034;	// L1627
      txp_v[0] = 0;	// L1628
      int32_t v1035 = scred[0];	// L1629
      ac_int<33, true> v1036 = v1035;	// L1630
      ac_int<33, true> v1037 = v1036 - 1;	// L1631
      int32_t v1038 = v1037;	// L1632
      scred[0] = v1038;	// L1633
    }
    int32_t v1039 = txp_v[1];	// L1635
    bool v1040 = v1039 == 1;	// L1636
    int32_t v1041 = scred[1];	// L1637
    bool v1042 = v1041 > 0;	// L1638
    bool v1043 = v1040 & v1042;	// L1639
    if (v1043) {	// L1640
      ac_int<17, false> tws;	// L1641
      tws = 0;	// L1642
      ac_int<17, true> v1045 = tws;	// L1643
      ac_int<17, true> v1046;
      ap_int<17> v1046_tmp = v1045;
      v1046_tmp[0] = 1;      v1046 = v1046_tmp;	// L1644
      tws = v1046;	// L1645
      half v1047 = txp_d[1];	// L1646
      uint16_t v1048;
      union { half from; uint16_t to;} _converter_v1047_to_v1048 = {};
      _converter_v1047_to_v1048.from = v1047;
      v1048 = _converter_v1047_to_v1048.to;	// L1647
      ac_int<17, true> v1049 = tws;	// L1648
      ac_int<17, true> v1050;
      ap_int<17> v1050_tmp = v1049;
      v1050_tmp(16, 1) = v1048;
      v1050 = v1050_tmp;	// L1649
      tws = v1050;	// L1650
      ac_int<17, true> v1051 = tws;	// L1651
      txs_r = v1051;	// L1652
      txp_v[1] = 0;	// L1653
      int32_t v1052 = scred[1];	// L1654
      ac_int<33, true> v1053 = v1052;	// L1655
      ac_int<33, true> v1054 = v1053 - 1;	// L1656
      int32_t v1055 = v1054;	// L1657
      scred[1] = v1055;	// L1658
    }
    int32_t v1056 = txp_v[2];	// L1660
    bool v1057 = v1056 == 1;	// L1661
    int32_t v1058 = scred[2];	// L1662
    bool v1059 = v1058 > 0;	// L1663
    bool v1060 = v1057 & v1059;	// L1664
    if (v1060) {	// L1665
      ac_int<17, false> tww;	// L1666
      tww = 0;	// L1667
      ac_int<17, true> v1062 = tww;	// L1668
      ac_int<17, true> v1063;
      ap_int<17> v1063_tmp = v1062;
      v1063_tmp[0] = 1;      v1063 = v1063_tmp;	// L1669
      tww = v1063;	// L1670
      half v1064 = txp_d[2];	// L1671
      uint16_t v1065;
      union { half from; uint16_t to;} _converter_v1064_to_v1065 = {};
      _converter_v1064_to_v1065.from = v1064;
      v1065 = _converter_v1064_to_v1065.to;	// L1672
      ac_int<17, true> v1066 = tww;	// L1673
      ac_int<17, true> v1067;
      ap_int<17> v1067_tmp = v1066;
      v1067_tmp(16, 1) = v1065;
      v1067 = v1067_tmp;	// L1674
      tww = v1067;	// L1675
      ac_int<17, true> v1068 = tww;	// L1676
      txw_r = v1068;	// L1677
      txp_v[2] = 0;	// L1678
      int32_t v1069 = scred[2];	// L1679
      ac_int<33, true> v1070 = v1069;	// L1680
      ac_int<33, true> v1071 = v1070 - 1;	// L1681
      int32_t v1072 = v1071;	// L1682
      scred[2] = v1072;	// L1683
    }
    int32_t v1073 = txp_v[3];	// L1685
    bool v1074 = v1073 == 1;	// L1686
    int32_t v1075 = scred[3];	// L1687
    bool v1076 = v1075 > 0;	// L1688
    bool v1077 = v1074 & v1076;	// L1689
    if (v1077) {	// L1690
      ac_int<17, false> twe;	// L1691
      twe = 0;	// L1692
      ac_int<17, true> v1079 = twe;	// L1693
      ac_int<17, true> v1080;
      ap_int<17> v1080_tmp = v1079;
      v1080_tmp[0] = 1;      v1080 = v1080_tmp;	// L1694
      twe = v1080;	// L1695
      half v1081 = txp_d[3];	// L1696
      uint16_t v1082;
      union { half from; uint16_t to;} _converter_v1081_to_v1082 = {};
      _converter_v1081_to_v1082.from = v1081;
      v1082 = _converter_v1081_to_v1082.to;	// L1697
      ac_int<17, true> v1083 = twe;	// L1698
      ac_int<17, true> v1084;
      ap_int<17> v1084_tmp = v1083;
      v1084_tmp(16, 1) = v1082;
      v1084 = v1084_tmp;	// L1699
      twe = v1084;	// L1700
      ac_int<17, true> v1085 = twe;	// L1701
      txe_r = v1085;	// L1702
      txp_v[3] = 0;	// L1703
      int32_t v1086 = scred[3];	// L1704
      ac_int<33, true> v1087 = v1086;	// L1705
      ac_int<33, true> v1088 = v1087 - 1;	// L1706
      int32_t v1089 = v1088;	// L1707
      scred[3] = v1089;	// L1708
    }
    int32_t v1090 = crv_vld;	// L1710
    bool v1091 = v1090 == 1;	// L1711
    if (v1091) {	// L1712
      int32_t v1092 = crv_mode;	// L1713
      bool v1093 = v1092 == 1;	// L1714
      if (v1093) {	// L1715
        int32_t v1094 = crv_addr;	// L1716
        int32_t v1095 = v1094 >> 3;	// L1717
        int32_t v1096 = v1095 & 1;	// L1718
        bool v1097 = v1096 == 1;	// L1719
        if (v1097) {	// L1720
          int32_t v1098 = crv_raw;	// L1721
          int32_t v1099 = crv_addr;	// L1722
          int32_t v1100 = v1099 & 7;	// L1723
          int v1101 = v1100;	// L1724
          irf[v1101] = v1098;	// L1725
        } else {
          int32_t v1102 = crv_addr;	// L1727
          bool v1103 = v1102 == 0;	// L1728
          if (v1103) {	// L1729
            int32_t v1104 = crv_raw;	// L1730
            int32_t v1105 = v1104 & 255;	// L1731
            dsmask = v1105;	// L1732
            int32_t v1106 = crv_raw;	// L1733
            int32_t v1107 = v1106 >> 8;	// L1734
            int32_t v1108 = v1107 & 7;	// L1735
            cfg_isz = v1108;	// L1736
            int32_t v1109 = crv_raw;	// L1737
            int32_t v1110 = v1109 >> 15;	// L1738
            int32_t v1111 = v1110 & 1;	// L1739
            bool v1112 = v1111 == 1;	// L1740
            if (v1112) {	// L1741
              fetch_en = 1;	// L1742
              instr_cnt = 0;	// L1743
              iter_cnt = 0;	// L1744
            }
          } else {
            int32_t v1113 = crv_addr;	// L1747
            bool v1114 = v1113 == 1;	// L1748
            if (v1114) {	// L1749
              int32_t v1115 = crv_raw;	// L1750
              int32_t v1116 = v1115 & 255;	// L1751
              cfg_itsz = v1116;	// L1752
            }
          }
        }
      } else {
        int32_t v1117 = crv_addr;	// L1757
        int32_t v1118 = v1117 >> 2;	// L1758
        int32_t v1119 = v1118 & 3;	// L1759
        bool v1120 = v1119 == 3;	// L1760
        if (v1120) {	// L1761
          int32_t v1121 = crv_addr;	// L1762
          int32_t v1122 = v1121 & 3;	// L1763
          int v1123 = v1122;	// L1764
          txp_v[v1123] = 1;	// L1765
          half v1124 = crv_data;	// L1766
          int32_t v1125 = crv_addr;	// L1767
          int32_t v1126 = v1125 & 3;	// L1768
          int v1127 = v1126;	// L1769
          txp_d[v1127] = v1124;	// L1770
          int32_t v1128 = crv_addr;	// L1771
          int32_t v1129 = v1128 & 3;	// L1772
          int v1130 = v1129;	// L1773
          txp_r[v1130] = 1;	// L1774
        } else {
          int32_t v1131 = crv_addr;	// L1776
          bool v1132 = v1131 < 8;	// L1777
          int32_t v1133 = dsmask;	// L1778
          int32_t v1134 = v1133 >> v1131;	// L1780
          int32_t v1135 = v1134 & 1;	// L1781
          bool v1136 = v1135 == 1;	// L1782
          bool v1137 = v1132 & v1136;	// L1783
          if (v1137) {	// L1784
            int32_t v1138 = crv_addr;	// L1785
            int v1139 = v1138;	// L1786
            int32_t v1140 = drf_full[v1139];	// L1787
            bool v1141 = v1140 == 0;	// L1788
            if (v1141) {	// L1789
              half v1142 = crv_data;	// L1790
              int32_t v1143 = crv_addr;	// L1791
              int v1144 = v1143;	// L1792
              drf[v1144] = v1142;	// L1793
              int32_t v1145 = crv_addr;	// L1794
              int v1146 = v1145;	// L1795
              drf_full[v1146] = 1;	// L1796
            }
          } else {
            half v1147 = crv_data;	// L1799
            int32_t v1148 = crv_addr;	// L1800
            int v1149 = v1148;	// L1801
            drf[v1149] = v1147;	// L1802
          }
        }
      }
    }
    ac_int<26, true> v1150 = oe_r;	// L1807
    v0.write(v1150);	// L1808
    ac_int<26, true> v1151 = ow_r;	// L1809
    v1.write(v1151);	// L1810
    ac_int<26, true> v1152 = os_r;	// L1811
    v2.write(v1152);	// L1812
    ac_int<26, true> v1153 = on_r;	// L1813
    v3.write(v1153);	// L1814
    ac_int<17, true> v1154 = txe_r;	// L1815
    v4.write(v1154);	// L1816
    ac_int<17, true> v1155 = txw_r;	// L1817
    v5.write(v1155);	// L1818
    ac_int<17, true> v1156 = txs_r;	// L1819
    v6.write(v1156);	// L1820
    ac_int<17, true> v1157 = txn_r;	// L1821
    v7.write(v1157);	// L1822
    int8_t v1158 = cre_r;	// L1823
    v8.write(v1158);	// L1824
    int8_t v1159 = crw_r;	// L1825
    v9.write(v1159);	// L1826
    int8_t v1160 = crs_r;	// L1827
    v10.write(v1160);	// L1828
    int8_t v1161 = crn_r;	// L1829
    v11.write(v1161);	// L1830
    int32_t v1162 = sc_r[0];	// L1831
    v14.write(v1162);	// L1832
    int32_t v1163 = sc_r[1];	// L1833
    v15.write(v1163);	// L1834
    int32_t v1164 = sc_r[2];	// L1835
    v12.write(v1164);	// L1836
    int32_t v1165 = sc_r[3];	// L1837
    v13.write(v1165);	// L1838
  }
}

void node_0_1(
  ac_channel< ac_int<26, false> >& v1166,
  ac_channel< ac_int<26, false> >& v1167,
  ac_channel< ac_int<26, false> >& v1168,
  ac_channel< ac_int<26, false> >& v1169,
  ac_channel< ac_int<17, false> >& v1170,
  ac_channel< ac_int<17, false> >& v1171,
  ac_channel< ac_int<17, false> >& v1172,
  ac_channel< ac_int<17, false> >& v1173,
  ac_channel< int32_t >& v1174,
  ac_channel< int32_t >& v1175,
  ac_channel< int32_t >& v1176,
  ac_channel< int32_t >& v1177,
  ac_channel< int32_t >& v1178,
  ac_channel< int32_t >& v1179,
  ac_channel< int32_t >& v1180,
  ac_channel< int32_t >& v1181,
  ac_channel< ac_int<26, false> >& v1182,
  ac_channel< ac_int<26, false> >& v1183,
  ac_channel< ac_int<26, false> >& v1184,
  ac_channel< ac_int<26, false> >& v1185,
  ac_channel< int32_t >& v1186,
  ac_channel< int32_t >& v1187,
  ac_channel< int32_t >& v1188,
  ac_channel< int32_t >& v1189,
  ac_channel< int32_t >& v1190,
  ac_channel< int32_t >& v1191,
  ac_channel< int32_t >& v1192,
  ac_channel< int32_t >& v1193,
  ac_channel< ac_int<17, false> >& v1194,
  ac_channel< ac_int<17, false> >& v1195,
  ac_channel< ac_int<17, false> >& v1196,
  ac_channel< ac_int<17, false> >& v1197
) {	// L1842
  int32_t irf1[8];	// L1879
  for (int v1199 = 0; v1199 < 8; v1199++) {	// L1880
    irf1[v1199] = 0;	// L1880
  }
  half drf1[8];	// L1881
  for (int v1201 = 0; v1201 < 8; v1201++) {	// L1882
    drf1[v1201] = (double)0.000000;	// L1882
  }
  int32_t drf_full1[8];	// L1883
  for (int v1203 = 0; v1203 < 8; v1203++) {	// L1884
    drf_full1[v1203] = 0;	// L1884
  }
  int32_t dsmask1;	// L1885
  dsmask1 = 0;	// L1886
  int32_t crv_vld1;	// L1887
  crv_vld1 = 0;	// L1888
  half crv_data1;	// L1889
  crv_data1 = (double)0.000000;	// L1890
  int32_t crv_addr1;	// L1891
  crv_addr1 = 0;	// L1892
  int32_t crv_mode1;	// L1893
  crv_mode1 = 0;	// L1894
  int32_t crv_raw1;	// L1895
  crv_raw1 = 0;	// L1896
  int32_t csd_vld1;	// L1897
  csd_vld1 = 0;	// L1898
  ac_int<26, false> csd_pkt1;	// L1899
  csd_pkt1 = 0;	// L1900
  int32_t csd_dir1;	// L1901
  csd_dir1 = 0;	// L1902
  int32_t row_id1;	// L1903
  row_id1 = 0;	// L1904
  int32_t col_id1;	// L1905
  col_id1 = 1;	// L1906
  ac_int<26, false> oe_r1;	// L1907
  oe_r1 = 0;	// L1908
  ac_int<26, false> ow_r1;	// L1909
  ow_r1 = 0;	// L1910
  ac_int<26, false> on_r1;	// L1911
  on_r1 = 0;	// L1912
  ac_int<26, false> os_r1;	// L1913
  os_r1 = 0;	// L1914
  ac_int<17, false> txn_r1;	// L1915
  txn_r1 = 0;	// L1916
  ac_int<17, false> txs_r1;	// L1917
  txs_r1 = 0;	// L1918
  ac_int<17, false> txw_r1;	// L1919
  txw_r1 = 0;	// L1920
  ac_int<17, false> txe_r1;	// L1921
  txe_r1 = 0;	// L1922
  half hold_v1[4][2];	// L1923
  for (int v1224 = 0; v1224 < 4; v1224++) {	// L1924
    for (int v1225 = 0; v1225 < 2; v1225++) {	// L1924
      hold_v1[v1224][v1225] = (double)0.000000;	// L1924
    }
  }
  uint8_t hold_cnt1[4];	// L1925
  for (int v1227 = 0; v1227 < 4; v1227++) {	// L1926
    hold_cnt1[v1227] = 0;	// L1926
  }
  ac_int<26, false> rbuf1[4][2];	// L1927
  for (int v1229 = 0; v1229 < 4; v1229++) {	// L1928
    for (int v1230 = 0; v1230 < 2; v1230++) {	// L1928
      rbuf1[v1229][v1230] = 0;	// L1928
    }
  }
  uint8_t rbcnt1[4];	// L1929
  for (int v1232 = 0; v1232 < 4; v1232++) {	// L1930
    rbcnt1[v1232] = 0;	// L1930
  }
  uint8_t rcred1[4];	// L1931
  for (int v1234 = 0; v1234 < 4; v1234++) {	// L1932
    rcred1[v1234] = 0;	// L1932
  }
  uint8_t cre_r1;	// L1933
  cre_r1 = 2;	// L1934
  uint8_t crw_r1;	// L1935
  crw_r1 = 2;	// L1936
  uint8_t crs_r1;	// L1937
  crs_r1 = 2;	// L1938
  uint8_t crn_r1;	// L1939
  crn_r1 = 2;	// L1940
  int32_t scred1[4];	// L1941
  for (int v1240 = 0; v1240 < 4; v1240++) {	// L1942
    scred1[v1240] = 0;	// L1942
  }
  int32_t txp_v1[4];	// L1943
  for (int v1242 = 0; v1242 < 4; v1242++) {	// L1944
    txp_v1[v1242] = 0;	// L1944
  }
  half txp_d1[4];	// L1945
  for (int v1244 = 0; v1244 < 4; v1244++) {	// L1946
    txp_d1[v1244] = (double)0.000000;	// L1946
  }
  int32_t txp_r1[4];	// L1947
  for (int v1246 = 0; v1246 < 4; v1246++) {	// L1948
    txp_r1[v1246] = 0;	// L1948
  }
  int32_t sc_r1[4];	// L1949
  for (int v1248 = 0; v1248 < 4; v1248++) {	// L1950
    sc_r1[v1248] = 2;	// L1950
  }
  int32_t cfg_isz1;	// L1951
  cfg_isz1 = 0;	// L1952
  int32_t cfg_itsz1;	// L1953
  cfg_itsz1 = 0;	// L1954
  uint8_t fetch_en1;	// L1955
  fetch_en1 = 0;	// L1956
  uint8_t instr_cnt1;	// L1957
  instr_cnt1 = 0;	// L1958
  uint8_t iter_cnt1;	// L1959
  iter_cnt1 = 0;	// L1960
  uint8_t condition_reg1;	// L1961
  condition_reg1 = 0;	// L1962
  uint8_t sb_v1[5];	// L1963
  for (int v1256 = 0; v1256 < 5; v1256++) {	// L1964
    sb_v1[v1256] = 0;	// L1964
  }
  uint8_t sb_dst1[5];	// L1965
  for (int v1258 = 0; v1258 < 5; v1258++) {	// L1966
    sb_dst1[v1258] = 0;	// L1966
  }
  uint8_t sb_cmp1[5];	// L1967
  for (int v1260 = 0; v1260 < 5; v1260++) {	// L1968
    sb_cmp1[v1260] = 0;	// L1968
  }
  uint8_t sb_rtr1[5];	// L1969
  for (int v1262 = 0; v1262 < 5; v1262++) {	// L1970
    sb_rtr1[v1262] = 0;	// L1970
  }
  uint8_t sb_inj1[5];	// L1971
  for (int v1264 = 0; v1264 < 5; v1264++) {	// L1972
    sb_inj1[v1264] = 0;	// L1972
  }
  uint8_t sb_dir1[5];	// L1973
  for (int v1266 = 0; v1266 < 5; v1266++) {	// L1974
    sb_dir1[v1266] = 0;	// L1974
  }
  uint8_t sb_id1[5];	// L1975
  for (int v1268 = 0; v1268 < 5; v1268++) {	// L1976
    sb_id1[v1268] = 0;	// L1976
  }
  uint8_t sb_rvld1[5];	// L1977
  for (int v1270 = 0; v1270 < 5; v1270++) {	// L1978
    sb_rvld1[v1270] = 0;	// L1978
  }
  uint8_t sb_ix1[5];	// L1979
  for (int v1272 = 0; v1272 < 5; v1272++) {	// L1980
    sb_ix1[v1272] = 0;	// L1980
  }
  uint8_t sb_long1[5];	// L1981
  for (int v1274 = 0; v1274 < 5; v1274++) {	// L1982
    sb_long1[v1274] = 0;	// L1982
  }
  half resq1[8];	// L1983
  for (int v1276 = 0; v1276 < 8; v1276++) {	// L1984
    resq1[v1276] = (double)0.000000;	// L1984
  }
  uint8_t cmpq1[8];	// L1985
  for (int v1278 = 0; v1278 < 8; v1278++) {	// L1986
    cmpq1[v1278] = 0;	// L1986
  }
  uint8_t resq_wr1;	// L1987
  resq_wr1 = 0;	// L1988
  ac_int<26, false> zpkt1;	// L1989
  zpkt1 = 0;	// L1990
  ac_int<17, false> zsys1;	// L1991
  zsys1 = 0;	// L1992
  int32_t zcr1;	// L1993
  zcr1 = 0;	// L1994
  ac_int<26, true> v1283 = zpkt1;	// L1995
  v1166.write(v1283);	// L1996
  ac_int<26, true> v1284 = zpkt1;	// L1997
  v1167.write(v1284);	// L1998
  ac_int<26, true> v1285 = zpkt1;	// L1999
  v1168.write(v1285);	// L2000
  ac_int<26, true> v1286 = zpkt1;	// L2001
  v1169.write(v1286);	// L2002
  ac_int<17, true> v1287 = zsys1;	// L2003
  v1170.write(v1287);	// L2004
  ac_int<17, true> v1288 = zsys1;	// L2005
  v1171.write(v1288);	// L2006
  ac_int<17, true> v1289 = zsys1;	// L2007
  v1172.write(v1289);	// L2008
  ac_int<17, true> v1290 = zsys1;	// L2009
  v1173.write(v1290);	// L2010
  int32_t v1291 = zcr1;	// L2011
  v1174.write(v1291);	// L2012
  int32_t v1292 = zcr1;	// L2013
  v1175.write(v1292);	// L2014
  int32_t v1293 = zcr1;	// L2015
  v1176.write(v1293);	// L2016
  int32_t v1294 = zcr1;	// L2017
  v1177.write(v1294);	// L2018
  int32_t v1295 = zcr1;	// L2019
  v1178.write(v1295);	// L2020
  int32_t v1296 = zcr1;	// L2021
  v1179.write(v1296);	// L2022
  int32_t v1297 = zcr1;	// L2023
  v1180.write(v1297);	// L2024
  int32_t v1298 = zcr1;	// L2025
  v1181.write(v1298);	// L2026
  ac_int<26, true> v1299 = zpkt1;	// L2027
  v1166.write(v1299);	// L2028
  ac_int<26, true> v1300 = zpkt1;	// L2029
  v1167.write(v1300);	// L2030
  ac_int<26, true> v1301 = zpkt1;	// L2031
  v1168.write(v1301);	// L2032
  ac_int<26, true> v1302 = zpkt1;	// L2033
  v1169.write(v1302);	// L2034
  ac_int<17, true> v1303 = zsys1;	// L2035
  v1170.write(v1303);	// L2036
  ac_int<17, true> v1304 = zsys1;	// L2037
  v1171.write(v1304);	// L2038
  ac_int<17, true> v1305 = zsys1;	// L2039
  v1172.write(v1305);	// L2040
  ac_int<17, true> v1306 = zsys1;	// L2041
  v1173.write(v1306);	// L2042
  int32_t v1307 = zcr1;	// L2043
  v1174.write(v1307);	// L2044
  int32_t v1308 = zcr1;	// L2045
  v1175.write(v1308);	// L2046
  int32_t v1309 = zcr1;	// L2047
  v1176.write(v1309);	// L2048
  int32_t v1310 = zcr1;	// L2049
  v1177.write(v1310);	// L2050
  int32_t v1311 = zcr1;	// L2051
  v1178.write(v1311);	// L2052
  int32_t v1312 = zcr1;	// L2053
  v1179.write(v1312);	// L2054
  int32_t v1313 = zcr1;	// L2055
  v1180.write(v1313);	// L2056
  int32_t v1314 = zcr1;	// L2057
  v1181.write(v1314);	// L2058
  ac_int<26, true> v1315 = zpkt1;	// L2059
  v1166.write(v1315);	// L2060
  ac_int<26, true> v1316 = zpkt1;	// L2061
  v1167.write(v1316);	// L2062
  ac_int<26, true> v1317 = zpkt1;	// L2063
  v1168.write(v1317);	// L2064
  ac_int<26, true> v1318 = zpkt1;	// L2065
  v1169.write(v1318);	// L2066
  ac_int<17, true> v1319 = zsys1;	// L2067
  v1170.write(v1319);	// L2068
  ac_int<17, true> v1320 = zsys1;	// L2069
  v1171.write(v1320);	// L2070
  ac_int<17, true> v1321 = zsys1;	// L2071
  v1172.write(v1321);	// L2072
  ac_int<17, true> v1322 = zsys1;	// L2073
  v1173.write(v1322);	// L2074
  int32_t v1323 = zcr1;	// L2075
  v1174.write(v1323);	// L2076
  int32_t v1324 = zcr1;	// L2077
  v1175.write(v1324);	// L2078
  int32_t v1325 = zcr1;	// L2079
  v1176.write(v1325);	// L2080
  int32_t v1326 = zcr1;	// L2081
  v1177.write(v1326);	// L2082
  int32_t v1327 = zcr1;	// L2083
  v1178.write(v1327);	// L2084
  int32_t v1328 = zcr1;	// L2085
  v1179.write(v1328);	// L2086
  int32_t v1329 = zcr1;	// L2087
  v1180.write(v1329);	// L2088
  int32_t v1330 = zcr1;	// L2089
  v1181.write(v1330);	// L2090
  ac_int<26, true> v1331 = zpkt1;	// L2091
  v1166.write(v1331);	// L2092
  ac_int<26, true> v1332 = zpkt1;	// L2093
  v1167.write(v1332);	// L2094
  ac_int<26, true> v1333 = zpkt1;	// L2095
  v1168.write(v1333);	// L2096
  ac_int<26, true> v1334 = zpkt1;	// L2097
  v1169.write(v1334);	// L2098
  ac_int<17, true> v1335 = zsys1;	// L2099
  v1170.write(v1335);	// L2100
  ac_int<17, true> v1336 = zsys1;	// L2101
  v1171.write(v1336);	// L2102
  ac_int<17, true> v1337 = zsys1;	// L2103
  v1172.write(v1337);	// L2104
  ac_int<17, true> v1338 = zsys1;	// L2105
  v1173.write(v1338);	// L2106
  int32_t v1339 = zcr1;	// L2107
  v1174.write(v1339);	// L2108
  int32_t v1340 = zcr1;	// L2109
  v1175.write(v1340);	// L2110
  int32_t v1341 = zcr1;	// L2111
  v1176.write(v1341);	// L2112
  int32_t v1342 = zcr1;	// L2113
  v1177.write(v1342);	// L2114
  int32_t v1343 = zcr1;	// L2115
  v1178.write(v1343);	// L2116
  int32_t v1344 = zcr1;	// L2117
  v1179.write(v1344);	// L2118
  int32_t v1345 = zcr1;	// L2119
  v1180.write(v1345);	// L2120
  int32_t v1346 = zcr1;	// L2121
  v1181.write(v1346);	// L2122
  ac_int<26, true> v1347 = zpkt1;	// L2123
  v1166.write(v1347);	// L2124
  ac_int<26, true> v1348 = zpkt1;	// L2125
  v1167.write(v1348);	// L2126
  ac_int<26, true> v1349 = zpkt1;	// L2127
  v1168.write(v1349);	// L2128
  ac_int<26, true> v1350 = zpkt1;	// L2129
  v1169.write(v1350);	// L2130
  ac_int<17, true> v1351 = zsys1;	// L2131
  v1170.write(v1351);	// L2132
  ac_int<17, true> v1352 = zsys1;	// L2133
  v1171.write(v1352);	// L2134
  ac_int<17, true> v1353 = zsys1;	// L2135
  v1172.write(v1353);	// L2136
  ac_int<17, true> v1354 = zsys1;	// L2137
  v1173.write(v1354);	// L2138
  int32_t v1355 = zcr1;	// L2139
  v1174.write(v1355);	// L2140
  int32_t v1356 = zcr1;	// L2141
  v1175.write(v1356);	// L2142
  int32_t v1357 = zcr1;	// L2143
  v1176.write(v1357);	// L2144
  int32_t v1358 = zcr1;	// L2145
  v1177.write(v1358);	// L2146
  int32_t v1359 = zcr1;	// L2147
  v1178.write(v1359);	// L2148
  int32_t v1360 = zcr1;	// L2149
  v1179.write(v1360);	// L2150
  int32_t v1361 = zcr1;	// L2151
  v1180.write(v1361);	// L2152
  int32_t v1362 = zcr1;	// L2153
  v1181.write(v1362);	// L2154
  ac_int<26, true> v1363 = oe_r1;	// L2155
  v1166.write(v1363);	// L2156
  ac_int<26, true> v1364 = ow_r1;	// L2157
  v1167.write(v1364);	// L2158
  ac_int<26, true> v1365 = os_r1;	// L2159
  v1168.write(v1365);	// L2160
  ac_int<26, true> v1366 = on_r1;	// L2161
  v1169.write(v1366);	// L2162
  ac_int<17, true> v1367 = txe_r1;	// L2163
  v1170.write(v1367);	// L2164
  ac_int<17, true> v1368 = txw_r1;	// L2165
  v1171.write(v1368);	// L2166
  ac_int<17, true> v1369 = txs_r1;	// L2167
  v1172.write(v1369);	// L2168
  ac_int<17, true> v1370 = txn_r1;	// L2169
  v1173.write(v1370);	// L2170
  int8_t v1371 = cre_r1;	// L2171
  v1174.write(v1371);	// L2172
  int8_t v1372 = crw_r1;	// L2173
  v1175.write(v1372);	// L2174
  int8_t v1373 = crs_r1;	// L2175
  v1176.write(v1373);	// L2176
  int8_t v1374 = crn_r1;	// L2177
  v1177.write(v1374);	// L2178
  int32_t v1375 = sc_r1[0];	// L2179
  v1180.write(v1375);	// L2180
  int32_t v1376 = sc_r1[1];	// L2181
  v1181.write(v1376);	// L2182
  int32_t v1377 = sc_r1[2];	// L2183
  v1178.write(v1377);	// L2184
  int32_t v1378 = sc_r1[3];	// L2185
  v1179.write(v1378);	// L2186
  l_S_t_0_t1: for (int t1 = 0; t1 < 10; t1++) {	// L2187
    ac_int<26, false> v1380 = v1182.read();	// L2188
    ac_int<26, false> p_w1;	// L2189
    p_w1 = v1380;	// L2190
    ac_int<26, false> v1382 = v1183.read();	// L2191
    ac_int<26, false> p_e1;	// L2192
    p_e1 = v1382;	// L2193
    ac_int<26, false> v1384 = v1184.read();	// L2194
    ac_int<26, false> p_n1;	// L2195
    p_n1 = v1384;	// L2196
    ac_int<26, false> v1386 = v1185.read();	// L2197
    ac_int<26, false> p_s1;	// L2198
    p_s1 = v1386;	// L2199
    int32_t v1388 = v1186.read();	// L2200
    uint8_t v1389 = rcred1[0];	// L2201
    ac_int<33, true> v1390 = v1389;	// L2202
    ac_int<33, true> v1391 = v1388;	// L2203
    ac_int<33, true> v1392 = v1390 + v1391;	// L2204
    uint8_t v1393 = v1392;	// L2205
    rcred1[0] = v1393;	// L2206
    int32_t v1394 = v1187.read();	// L2207
    uint8_t v1395 = rcred1[1];	// L2208
    ac_int<33, true> v1396 = v1395;	// L2209
    ac_int<33, true> v1397 = v1394;	// L2210
    ac_int<33, true> v1398 = v1396 + v1397;	// L2211
    uint8_t v1399 = v1398;	// L2212
    rcred1[1] = v1399;	// L2213
    int32_t v1400 = v1188.read();	// L2214
    uint8_t v1401 = rcred1[2];	// L2215
    ac_int<33, true> v1402 = v1401;	// L2216
    ac_int<33, true> v1403 = v1400;	// L2217
    ac_int<33, true> v1404 = v1402 + v1403;	// L2218
    uint8_t v1405 = v1404;	// L2219
    rcred1[2] = v1405;	// L2220
    int32_t v1406 = v1189.read();	// L2221
    uint8_t v1407 = rcred1[3];	// L2222
    ac_int<33, true> v1408 = v1407;	// L2223
    ac_int<33, true> v1409 = v1406;	// L2224
    ac_int<33, true> v1410 = v1408 + v1409;	// L2225
    uint8_t v1411 = v1410;	// L2226
    rcred1[3] = v1411;	// L2227
    int32_t v1412 = v1190.read();	// L2228
    int32_t v1413 = scred1[0];	// L2229
    ac_int<33, true> v1414 = v1413;	// L2230
    ac_int<33, true> v1415 = v1412;	// L2231
    ac_int<33, true> v1416 = v1414 + v1415;	// L2232
    int32_t v1417 = v1416;	// L2233
    scred1[0] = v1417;	// L2234
    int32_t v1418 = v1191.read();	// L2235
    int32_t v1419 = scred1[1];	// L2236
    ac_int<33, true> v1420 = v1419;	// L2237
    ac_int<33, true> v1421 = v1418;	// L2238
    ac_int<33, true> v1422 = v1420 + v1421;	// L2239
    int32_t v1423 = v1422;	// L2240
    scred1[1] = v1423;	// L2241
    int32_t v1424 = v1192.read();	// L2242
    int32_t v1425 = scred1[2];	// L2243
    ac_int<33, true> v1426 = v1425;	// L2244
    ac_int<33, true> v1427 = v1424;	// L2245
    ac_int<33, true> v1428 = v1426 + v1427;	// L2246
    int32_t v1429 = v1428;	// L2247
    scred1[2] = v1429;	// L2248
    int32_t v1430 = v1193.read();	// L2249
    int32_t v1431 = scred1[3];	// L2250
    ac_int<33, true> v1432 = v1431;	// L2251
    ac_int<33, true> v1433 = v1430;	// L2252
    ac_int<33, true> v1434 = v1432 + v1433;	// L2253
    int32_t v1435 = v1434;	// L2254
    scred1[3] = v1435;	// L2255
    ac_int<26, false> fin1[4];	// L2256
    for (int v1437 = 0; v1437 < 4; v1437++) {	// L2257
      fin1[v1437] = 0;	// L2257
    }
    ac_int<26, true> v1438 = p_w1;	// L2258
    fin1[0] = v1438;	// L2259
    ac_int<26, true> v1439 = p_e1;	// L2260
    fin1[1] = v1439;	// L2261
    ac_int<26, true> v1440 = p_n1;	// L2262
    fin1[2] = v1440;	// L2263
    ac_int<26, true> v1441 = p_s1;	// L2264
    fin1[3] = v1441;	// L2265
    l_S_d_0_d5: for (int d5 = 0; d5 < 4; d5++) {	// L2266
      ac_int<26, false> v1443 = fin1[d5];	// L2267
      bool v1444;
      ap_int<26> v1444_tmp = v1443;
      v1444 = v1444_tmp[25];	// L2268
      int32_t v1445 = v1444;	// L2269
      bool v1446 = v1445 == 1;	// L2270
      uint8_t v1447 = rbcnt1[d5];	// L2271
      int32_t v1448 = v1447;	// L2272
      bool v1449 = v1448 < 2;	// L2273
      bool v1450 = v1446 & v1449;	// L2274
      if (v1450) {	// L2275
        ac_int<26, false> v1451 = fin1[d5];	// L2276
        uint8_t v1452 = rbcnt1[d5];	// L2277
        int v1453 = v1452;	// L2278
        rbuf1[d5][v1453] = v1451;	// L2279
        uint8_t v1454 = rbcnt1[d5];	// L2280
        ac_int<33, true> v1455 = v1454;	// L2281
        ac_int<33, true> v1456 = v1455 + 1;	// L2282
        uint8_t v1457 = v1456;	// L2283
        rbcnt1[d5] = v1457;	// L2284
      }
    }
    ac_int<26, false> hd1[4];	// L2287
    for (int v1459 = 0; v1459 < 4; v1459++) {	// L2288
      hd1[v1459] = 0;	// L2288
    }
    int32_t hvld1[4];	// L2289
    for (int v1461 = 0; v1461 < 4; v1461++) {	// L2290
      hvld1[v1461] = 0;	// L2290
    }
    int32_t hit1[4];	// L2291
    for (int v1463 = 0; v1463 < 4; v1463++) {	// L2292
      hit1[v1463] = 0;	// L2292
    }
    int32_t axis1[4];	// L2293
    for (int v1465 = 0; v1465 < 4; v1465++) {	// L2294
      axis1[v1465] = 0;	// L2294
    }
    int32_t v1466 = col_id1;	// L2295
    axis1[0] = v1466;	// L2296
    int32_t v1467 = col_id1;	// L2297
    axis1[1] = v1467;	// L2298
    int32_t v1468 = row_id1;	// L2299
    axis1[2] = v1468;	// L2300
    int32_t v1469 = row_id1;	// L2301
    axis1[3] = v1469;	// L2302
    l_S_d_1_d6: for (int d6 = 0; d6 < 4; d6++) {	// L2303
      uint8_t v1471 = rbcnt1[d6];	// L2304
      int32_t v1472 = v1471;	// L2305
      bool v1473 = v1472 > 0;	// L2306
      if (v1473) {	// L2307
        ac_int<26, false> v1474 = rbuf1[d6][0];	// L2308
        hd1[d6] = v1474;	// L2309
        hvld1[d6] = 1;	// L2310
        ac_int<26, false> v1475 = hd1[d6];	// L2311
        ac_int<4, true> v1476;
        ap_int<26> v1476_tmp = v1475;
        v1476 = v1476_tmp(24, 21);	// L2312
        int32_t v1477 = axis1[d6];	// L2313
        int32_t v1478 = v1476;	// L2314
        bool v1479 = v1478 == v1477;	// L2315
        if (v1479) {	// L2316
          hit1[d6] = 1;	// L2317
        }
      }
    }
    ac_int<26, false> o_crv1;	// L2321
    o_crv1 = 0;	// L2322
    int32_t crv_in1;	// L2323
    crv_in1 = -1;	// L2324
    int32_t v1482 = hit1[3];	// L2325
    bool v1483 = v1482 == 1;	// L2326
    if (v1483) {	// L2327
      ac_int<26, false> v1484 = hd1[3];	// L2328
      o_crv1 = v1484;	// L2329
      crv_in1 = 3;	// L2330
    } else {
      int32_t v1485 = hit1[2];	// L2332
      bool v1486 = v1485 == 1;	// L2333
      if (v1486) {	// L2334
        ac_int<26, false> v1487 = hd1[2];	// L2335
        o_crv1 = v1487;	// L2336
        crv_in1 = 2;	// L2337
      } else {
        int32_t v1488 = hit1[1];	// L2339
        bool v1489 = v1488 == 1;	// L2340
        if (v1489) {	// L2341
          ac_int<26, false> v1490 = hd1[1];	// L2342
          o_crv1 = v1490;	// L2343
          crv_in1 = 1;	// L2344
        } else {
          int32_t v1491 = hit1[0];	// L2346
          bool v1492 = v1491 == 1;	// L2347
          if (v1492) {	// L2348
            ac_int<26, false> v1493 = hd1[0];	// L2349
            o_crv1 = v1493;	// L2350
            crv_in1 = 0;	// L2351
          }
        }
      }
    }
    ac_int<26, false> o_out1[4];	// L2356
    for (int v1495 = 0; v1495 < 4; v1495++) {	// L2357
      o_out1[v1495] = 0;	// L2357
    }
    int32_t pop1[4];	// L2358
    for (int v1497 = 0; v1497 < 4; v1497++) {	// L2359
      pop1[v1497] = 0;	// L2359
    }
    int32_t inj_done1;	// L2360
    inj_done1 = 0;	// L2361
    int32_t idir1;	// L2362
    idir1 = -1;	// L2363
    ac_int<26, true> v1500 = csd_pkt1;	// L2364
    bool v1501;
    ap_int<26> v1501_tmp = v1500;
    v1501 = v1501_tmp[25];	// L2365
    int32_t v1502 = v1501;	// L2366
    bool v1503 = v1502 == 1;	// L2367
    if (v1503) {	// L2368
      int32_t v1504 = csd_dir1;	// L2369
      ac_int<33, true> v1505 = v1504;	// L2370
      ac_int<33, true> v1506 = 3 - v1505;	// L2371
      int32_t v1507 = v1506;	// L2372
      idir1 = v1507;	// L2373
    }
    l_S_o_2_o1: for (int o1 = 0; o1 < 4; o1++) {	// L2375
      uint8_t v1509 = rcred1[o1];	// L2376
      int32_t v1510 = v1509;	// L2377
      bool v1511 = v1510 > 0;	// L2378
      if (v1511) {	// L2379
        int32_t v1512 = idir1;	// L2380
        ac_int<33, true> v1513 = v1512;	// L2381
        ac_int<33, true> v1514 = o1;	// L2382
        bool v1515 = v1513 == v1514;	// L2383
        if (v1515) {	// L2384
          ac_int<26, true> v1516 = csd_pkt1;	// L2385
          o_out1[o1] = v1516;	// L2386
          uint8_t v1517 = rcred1[o1];	// L2387
          ac_int<33, true> v1518 = v1517;	// L2388
          ac_int<33, true> v1519 = v1518 - 1;	// L2389
          uint8_t v1520 = v1519;	// L2390
          rcred1[o1] = v1520;	// L2391
          inj_done1 = 1;	// L2392
        } else {
          int32_t v1521 = hvld1[o1];	// L2394
          bool v1522 = v1521 == 1;	// L2395
          int32_t v1523 = hit1[o1];	// L2396
          bool v1524 = v1523 == 0;	// L2397
          bool v1525 = v1522 & v1524;	// L2398
          if (v1525) {	// L2399
            ac_int<26, false> v1526 = hd1[o1];	// L2400
            o_out1[o1] = v1526;	// L2401
            uint8_t v1527 = rcred1[o1];	// L2402
            ac_int<33, true> v1528 = v1527;	// L2403
            ac_int<33, true> v1529 = v1528 - 1;	// L2404
            uint8_t v1530 = v1529;	// L2405
            rcred1[o1] = v1530;	// L2406
            pop1[o1] = 1;	// L2407
          }
        }
      }
    }
    int32_t v1531 = crv_in1;	// L2412
    bool v1532 = v1531 >= 0;	// L2413
    if (v1532) {	// L2414
      int32_t v1533 = crv_in1;	// L2415
      int v1534 = v1533;	// L2416
      pop1[v1534] = 1;	// L2417
    }
    int32_t ret1[4];	// L2419
    for (int v1536 = 0; v1536 < 4; v1536++) {	// L2420
      ret1[v1536] = 0;	// L2420
    }
    l_S_d_3_d7: for (int d7 = 0; d7 < 4; d7++) {	// L2421
      int32_t v1538 = pop1[d7];	// L2422
      bool v1539 = v1538 == 1;	// L2423
      if (v1539) {	// L2424
        l_S_sft_3_sft1: for (int sft1 = 0; sft1 < 1; sft1++) {	// L2425
          ac_int<26, false> v1541 = rbuf1[d7][(sft1 + 1)];	// L2426
          rbuf1[d7][sft1] = v1541;	// L2427
        }
        uint8_t v1542 = rbcnt1[d7];	// L2429
        ac_int<33, true> v1543 = v1542;	// L2430
        ac_int<33, true> v1544 = v1543 - 1;	// L2431
        uint8_t v1545 = v1544;	// L2432
        rbcnt1[d7] = v1545;	// L2433
        ret1[d7] = 1;	// L2434
      }
    }
    int32_t v1546 = ret1[0];	// L2437
    uint8_t v1547 = v1546;	// L2438
    cre_r1 = v1547;	// L2439
    int32_t v1548 = ret1[1];	// L2440
    uint8_t v1549 = v1548;	// L2441
    crw_r1 = v1549;	// L2442
    int32_t v1550 = ret1[2];	// L2443
    uint8_t v1551 = v1550;	// L2444
    crs_r1 = v1551;	// L2445
    int32_t v1552 = ret1[3];	// L2446
    uint8_t v1553 = v1552;	// L2447
    crn_r1 = v1553;	// L2448
    ac_int<26, false> v1554 = o_out1[0];	// L2449
    oe_r1 = v1554;	// L2450
    ac_int<26, false> v1555 = o_out1[1];	// L2451
    ow_r1 = v1555;	// L2452
    ac_int<26, false> v1556 = o_out1[2];	// L2453
    os_r1 = v1556;	// L2454
    ac_int<26, false> v1557 = o_out1[3];	// L2455
    on_r1 = v1557;	// L2456
    int32_t v1558 = inj_done1;	// L2457
    bool v1559 = v1558 == 1;	// L2458
    if (v1559) {	// L2459
      csd_pkt1 = 0;	// L2460
    }
    ac_int<26, true> v1560 = o_crv1;	// L2462
    bool v1561;
    ap_int<26> v1561_tmp = v1560;
    v1561 = v1561_tmp[25];	// L2463
    int32_t v1562 = v1561;	// L2464
    crv_vld1 = v1562;	// L2465
    ac_int<26, true> v1563 = o_crv1;	// L2466
    int16_t v1564;
    ap_int<26> v1564_tmp = v1563;
    v1564 = v1564_tmp(15, 0);	// L2467
    half v1565;
    union { uint16_t from; half to;} _converter_v1564_to_v1565 = {};
    _converter_v1564_to_v1565.from = v1564;
    v1565 = _converter_v1564_to_v1565.to;	// L2468
    crv_data1 = v1565;	// L2469
    ac_int<26, true> v1566 = o_crv1;	// L2470
    ac_int<4, true> v1567;
    ap_int<26> v1567_tmp = v1566;
    v1567 = v1567_tmp(19, 16);	// L2471
    int32_t v1568 = v1567;	// L2472
    crv_addr1 = v1568;	// L2473
    ac_int<26, true> v1569 = o_crv1;	// L2474
    bool v1570;
    ap_int<26> v1570_tmp = v1569;
    v1570 = v1570_tmp[20];	// L2475
    int32_t v1571 = v1570;	// L2476
    crv_mode1 = v1571;	// L2477
    ac_int<26, true> v1572 = o_crv1;	// L2478
    int16_t v1573;
    ap_int<26> v1573_tmp = v1572;
    v1573 = v1573_tmp(15, 0);	// L2479
    int32_t v1574 = v1573;	// L2480
    crv_raw1 = v1574;	// L2481
    ac_int<17, false> v1575 = v1194.read();	// L2482
    ac_int<17, false> rx_w1;	// L2483
    rx_w1 = v1575;	// L2484
    ac_int<17, false> v1577 = v1195.read();	// L2485
    ac_int<17, false> rx_e1;	// L2486
    rx_e1 = v1577;	// L2487
    ac_int<17, false> v1579 = v1196.read();	// L2488
    ac_int<17, false> rx_n1;	// L2489
    rx_n1 = v1579;	// L2490
    ac_int<17, false> v1581 = v1197.read();	// L2491
    ac_int<17, false> rx_s1;	// L2492
    rx_s1 = v1581;	// L2493
    half rxv1[4];	// L2494
    for (int v1584 = 0; v1584 < 4; v1584++) {	// L2495
      rxv1[v1584] = (double)0.000000;	// L2495
    }
    int32_t rxvld1[4];	// L2496
    for (int v1586 = 0; v1586 < 4; v1586++) {	// L2497
      rxvld1[v1586] = 0;	// L2497
    }
    ac_int<17, true> v1587 = rx_n1;	// L2498
    int16_t v1588;
    ap_int<17> v1588_tmp = v1587;
    v1588 = v1588_tmp(16, 1);	// L2499
    half v1589;
    union { uint16_t from; half to;} _converter_v1588_to_v1589 = {};
    _converter_v1588_to_v1589.from = v1588;
    v1589 = _converter_v1588_to_v1589.to;	// L2500
    rxv1[0] = v1589;	// L2501
    ac_int<17, true> v1590 = rx_n1;	// L2502
    bool v1591;
    ap_int<17> v1591_tmp = v1590;
    v1591 = v1591_tmp[0];	// L2503
    int32_t v1592 = v1591;	// L2504
    rxvld1[0] = v1592;	// L2505
    ac_int<17, true> v1593 = rx_s1;	// L2506
    int16_t v1594;
    ap_int<17> v1594_tmp = v1593;
    v1594 = v1594_tmp(16, 1);	// L2507
    half v1595;
    union { uint16_t from; half to;} _converter_v1594_to_v1595 = {};
    _converter_v1594_to_v1595.from = v1594;
    v1595 = _converter_v1594_to_v1595.to;	// L2508
    rxv1[1] = v1595;	// L2509
    ac_int<17, true> v1596 = rx_s1;	// L2510
    bool v1597;
    ap_int<17> v1597_tmp = v1596;
    v1597 = v1597_tmp[0];	// L2511
    int32_t v1598 = v1597;	// L2512
    rxvld1[1] = v1598;	// L2513
    ac_int<17, true> v1599 = rx_w1;	// L2514
    int16_t v1600;
    ap_int<17> v1600_tmp = v1599;
    v1600 = v1600_tmp(16, 1);	// L2515
    half v1601;
    union { uint16_t from; half to;} _converter_v1600_to_v1601 = {};
    _converter_v1600_to_v1601.from = v1600;
    v1601 = _converter_v1600_to_v1601.to;	// L2516
    rxv1[2] = v1601;	// L2517
    ac_int<17, true> v1602 = rx_w1;	// L2518
    bool v1603;
    ap_int<17> v1603_tmp = v1602;
    v1603 = v1603_tmp[0];	// L2519
    int32_t v1604 = v1603;	// L2520
    rxvld1[2] = v1604;	// L2521
    ac_int<17, true> v1605 = rx_e1;	// L2522
    int16_t v1606;
    ap_int<17> v1606_tmp = v1605;
    v1606 = v1606_tmp(16, 1);	// L2523
    half v1607;
    union { uint16_t from; half to;} _converter_v1606_to_v1607 = {};
    _converter_v1606_to_v1607.from = v1606;
    v1607 = _converter_v1606_to_v1607.to;	// L2524
    rxv1[3] = v1607;	// L2525
    ac_int<17, true> v1608 = rx_e1;	// L2526
    bool v1609;
    ap_int<17> v1609_tmp = v1608;
    v1609 = v1609_tmp[0];	// L2527
    int32_t v1610 = v1609;	// L2528
    rxvld1[3] = v1610;	// L2529
    l_S_d_5_d8: for (int d8 = 0; d8 < 4; d8++) {	// L2530
      int32_t v1612 = rxvld1[d8];	// L2531
      bool v1613 = v1612 == 1;	// L2532
      uint8_t v1614 = hold_cnt1[d8];	// L2533
      int32_t v1615 = v1614;	// L2534
      bool v1616 = v1615 < 2;	// L2535
      bool v1617 = v1613 & v1616;	// L2536
      if (v1617) {	// L2537
        half v1618 = rxv1[d8];	// L2538
        uint8_t v1619 = hold_cnt1[d8];	// L2539
        int v1620 = v1619;	// L2540
        hold_v1[d8][v1620] = v1618;	// L2541
        uint8_t v1621 = hold_cnt1[d8];	// L2542
        ac_int<33, true> v1622 = v1621;	// L2543
        ac_int<33, true> v1623 = v1622 + 1;	// L2544
        uint8_t v1624 = v1623;	// L2545
        hold_cnt1[d8] = v1624;	// L2546
      }
    }
    int32_t retire_ok1;	// L2549
    retire_ok1 = 1;	// L2550
    uint8_t v1626 = sb_v1[0];	// L2551
    int32_t v1627 = v1626;	// L2552
    bool v1628 = v1627 == 1;	// L2553
    uint8_t v1629 = sb_rtr1[0];	// L2554
    int32_t v1630 = v1629;	// L2555
    bool v1631 = v1630 == 0;	// L2556
    uint8_t v1632 = sb_dst1[0];	// L2557
    int32_t v1633 = v1632;	// L2558
    bool v1634 = v1633 >= 12;	// L2559
    bool v1635 = v1628 & v1631;	// L2560
    bool v1636 = v1635 & v1634;	// L2561
    if (v1636) {	// L2562
      uint8_t v1637 = sb_rvld1[0];	// L2563
      int32_t v1638 = v1637;	// L2564
      bool v1639 = v1638 == 1;	// L2565
      uint8_t v1640 = sb_dst1[0];	// L2566
      int32_t v1641 = v1640;	// L2567
      int32_t v1642 = v1641 & 3;	// L2568
      int v1643 = v1642;	// L2569
      int32_t v1644 = txp_v1[v1643];	// L2570
      bool v1645 = v1644 == 1;	// L2571
      bool v1646 = v1639 & v1645;	// L2572
      if (v1646) {	// L2573
        retire_ok1 = 0;	// L2574
      }
    }
    uint8_t v1647 = sb_v1[0];	// L2577
    int32_t v1648 = v1647;	// L2578
    bool v1649 = v1648 == 1;	// L2579
    int32_t v1650 = retire_ok1;	// L2580
    bool v1651 = v1650 == 1;	// L2581
    bool v1652 = v1649 & v1651;	// L2582
    if (v1652) {	// L2583
      uint8_t v1653 = sb_ix1[0];	// L2584
      int v1654 = v1653;	// L2585
      half v1655 = resq1[v1654];	// L2586
      half wb1;	// L2587
      wb1 = v1655;	// L2588
      uint8_t v1657 = sb_cmp1[0];	// L2589
      int32_t v1658 = v1657;	// L2590
      bool v1659 = v1658 == 1;	// L2591
      if (v1659) {	// L2592
        uint8_t v1660 = sb_ix1[0];	// L2593
        int v1661 = v1660;	// L2594
        uint8_t v1662 = cmpq1[v1661];	// L2595
        condition_reg1 = v1662;	// L2596
      }
      uint8_t v1663 = sb_rtr1[0];	// L2598
      int32_t v1664 = v1663;	// L2599
      bool v1665 = v1664 == 1;	// L2600
      if (v1665) {	// L2601
        uint8_t v1666 = sb_inj1[0];	// L2602
        int32_t v1667 = v1666;	// L2603
        bool v1668 = v1667 == 1;	// L2604
        ac_int<26, true> v1669 = csd_pkt1;	// L2605
        bool v1670;
        ap_int<26> v1670_tmp = v1669;
        v1670 = v1670_tmp[25];	// L2606
        int32_t v1671 = v1670;	// L2607
        bool v1672 = v1671 == 0;	// L2608
        bool v1673 = v1668 & v1672;	// L2609
        if (v1673) {	// L2610
          half v1674 = wb1;	// L2611
          uint16_t v1675;
          union { half from; uint16_t to;} _converter_v1674_to_v1675 = {};
          _converter_v1674_to_v1675.from = v1674;
          v1675 = _converter_v1674_to_v1675.to;	// L2612
          ac_int<26, true> v1676 = csd_pkt1;	// L2613
          ac_int<26, true> v1677;
          ap_int<26> v1677_tmp = v1676;
          v1677_tmp(15, 0) = v1675;
          v1677 = v1677_tmp;	// L2614
          csd_pkt1 = v1677;	// L2615
          uint8_t v1678 = sb_dst1[0];	// L2616
          ac_int<4, false> v1679 = v1678;	// L2617
          ac_int<26, true> v1680 = csd_pkt1;	// L2618
          ac_int<26, true> v1681;
          ap_int<26> v1681_tmp = v1680;
          v1681_tmp(19, 16) = v1679;
          v1681 = v1681_tmp;	// L2619
          csd_pkt1 = v1681;	// L2620
          uint8_t v1682 = sb_id1[0];	// L2621
          ac_int<4, false> v1683 = v1682;	// L2622
          ac_int<26, true> v1684 = csd_pkt1;	// L2623
          ac_int<26, true> v1685;
          ap_int<26> v1685_tmp = v1684;
          v1685_tmp(24, 21) = v1683;
          v1685 = v1685_tmp;	// L2624
          csd_pkt1 = v1685;	// L2625
          uint8_t v1686 = sb_rvld1[0];	// L2626
          bool v1687 = v1686;	// L2627
          ac_int<26, true> v1688 = csd_pkt1;	// L2628
          ac_int<26, true> v1689;
          ap_int<26> v1689_tmp = v1688;
          v1689_tmp[25] = v1687;          v1689 = v1689_tmp;	// L2629
          csd_pkt1 = v1689;	// L2630
          uint8_t v1690 = sb_dir1[0];	// L2631
          int32_t v1691 = v1690;	// L2632
          csd_dir1 = v1691;	// L2633
        }
      } else {
        uint8_t v1692 = sb_dst1[0];	// L2636
        int32_t v1693 = v1692;	// L2637
        bool v1694 = v1693 >= 12;	// L2638
        if (v1694) {	// L2639
          uint8_t v1695 = sb_rvld1[0];	// L2640
          int32_t v1696 = v1695;	// L2641
          bool v1697 = v1696 == 1;	// L2642
          if (v1697) {	// L2643
            uint8_t v1698 = sb_dst1[0];	// L2644
            int32_t v1699 = v1698;	// L2645
            int32_t v1700 = v1699 & 3;	// L2646
            int v1701 = v1700;	// L2647
            txp_v1[v1701] = 1;	// L2648
            half v1702 = wb1;	// L2649
            uint8_t v1703 = sb_dst1[0];	// L2650
            int32_t v1704 = v1703;	// L2651
            int32_t v1705 = v1704 & 3;	// L2652
            int v1706 = v1705;	// L2653
            txp_d1[v1706] = v1702;	// L2654
            uint8_t v1707 = sb_dst1[0];	// L2655
            int32_t v1708 = v1707;	// L2656
            int32_t v1709 = v1708 & 3;	// L2657
            int v1710 = v1709;	// L2658
            txp_r1[v1710] = 1;	// L2659
          }
        } else {
          uint8_t v1711 = sb_rvld1[0];	// L2662
          int32_t v1712 = v1711;	// L2663
          bool v1713 = v1712 == 1;	// L2664
          if (v1713) {	// L2665
            uint8_t v1714 = sb_dst1[0];	// L2666
            int32_t v1715 = v1714;	// L2667
            bool v1716 = v1715 < 8;	// L2668
            int32_t v1717 = dsmask1;	// L2669
            int32_t v1718 = v1717 >> v1715;	// L2672
            int32_t v1719 = v1718 & 1;	// L2673
            bool v1720 = v1719 == 1;	// L2674
            bool v1721 = v1716 & v1720;	// L2675
            if (v1721) {	// L2676
              uint8_t v1722 = sb_dst1[0];	// L2677
              int v1723 = v1722;	// L2678
              int32_t v1724 = drf_full1[v1723];	// L2679
              bool v1725 = v1724 == 0;	// L2680
              if (v1725) {	// L2681
                half v1726 = wb1;	// L2682
                uint8_t v1727 = sb_dst1[0];	// L2683
                int v1728 = v1727;	// L2684
                drf1[v1728] = v1726;	// L2685
                uint8_t v1729 = sb_dst1[0];	// L2686
                int v1730 = v1729;	// L2687
                drf_full1[v1730] = 1;	// L2688
              }
            } else {
              half v1731 = wb1;	// L2691
              uint8_t v1732 = sb_dst1[0];	// L2692
              int32_t v1733 = v1732;	// L2693
              int32_t v1734 = v1733 & 7;	// L2694
              int v1735 = v1734;	// L2695
              drf1[v1735] = v1731;	// L2696
            }
          }
        }
      }
    }
    int32_t pc1;	// L2702
    pc1 = -1;	// L2703
    int8_t v1737 = fetch_en1;	// L2704
    int32_t v1738 = v1737;	// L2705
    bool v1739 = v1738 == 1;	// L2706
    if (v1739) {	// L2707
      int8_t v1740 = instr_cnt1;	// L2708
      int32_t v1741 = v1740;	// L2709
      pc1 = v1741;	// L2710
    }
    int32_t instr1;	// L2712
    instr1 = 0;	// L2713
    int32_t v1743 = pc1;	// L2714
    bool v1744 = v1743 >= 0;	// L2715
    if (v1744) {	// L2716
      int32_t v1745 = pc1;	// L2717
      int v1746 = v1745;	// L2718
      int32_t v1747 = irf1[v1746];	// L2719
      instr1 = v1747;	// L2720
    }
    int32_t v1748 = instr1;	// L2722
    int32_t v1749 = v1748 & 15;	// L2723
    int32_t op1;	// L2724
    op1 = v1749;	// L2725
    int32_t v1751 = instr1;	// L2726
    int32_t v1752 = v1751 >> 4;	// L2727
    int32_t v1753 = v1752 & 15;	// L2728
    int32_t dst1;	// L2729
    dst1 = v1753;	// L2730
    int32_t v1755 = instr1;	// L2731
    int32_t v1756 = v1755 >> 8;	// L2732
    int32_t v1757 = v1756 & 15;	// L2733
    int32_t s11;	// L2734
    s11 = v1757;	// L2735
    int32_t v1759 = instr1;	// L2736
    int32_t v1760 = v1759 >> 12;	// L2737
    int32_t v1761 = v1760 & 15;	// L2738
    int32_t s21;	// L2739
    s21 = v1761;	// L2740
    half a1;	// L2741
    a1 = (double)0.000000;	// L2742
    half b1;	// L2743
    b1 = (double)0.000000;	// L2744
    int32_t v1765 = s11;	// L2745
    bool v1766 = v1765 >= 12;	// L2746
    if (v1766) {	// L2747
      int32_t v1767 = s11;	// L2748
      int32_t v1768 = v1767 & 3;	// L2749
      int v1769 = v1768;	// L2750
      half v1770 = hold_v1[v1769][0];	// L2751
      a1 = v1770;	// L2752
    } else {
      int32_t v1771 = s11;	// L2754
      int v1772 = v1771;	// L2755
      half v1773 = drf1[v1772];	// L2756
      a1 = v1773;	// L2757
    }
    int32_t v1774 = s21;	// L2759
    bool v1775 = v1774 >= 12;	// L2760
    if (v1775) {	// L2761
      int32_t v1776 = s21;	// L2762
      int32_t v1777 = v1776 & 3;	// L2763
      int v1778 = v1777;	// L2764
      half v1779 = hold_v1[v1778][0];	// L2765
      b1 = v1779;	// L2766
    } else {
      int32_t v1780 = s21;	// L2768
      int v1781 = v1780;	// L2769
      half v1782 = drf1[v1781];	// L2770
      b1 = v1782;	// L2771
    }
    int32_t a_vld1;	// L2773
    a_vld1 = 1;	// L2774
    int32_t b_vld1;	// L2775
    b_vld1 = 1;	// L2776
    int32_t v1785 = s11;	// L2777
    bool v1786 = v1785 >= 12;	// L2778
    if (v1786) {	// L2779
      a_vld1 = 0;	// L2780
      int32_t v1787 = s11;	// L2781
      int32_t v1788 = v1787 & 3;	// L2782
      int v1789 = v1788;	// L2783
      uint8_t v1790 = hold_cnt1[v1789];	// L2784
      int32_t v1791 = v1790;	// L2785
      bool v1792 = v1791 > 0;	// L2786
      if (v1792) {	// L2787
        a_vld1 = 1;	// L2788
      }
    }
    int32_t v1793 = s21;	// L2791
    bool v1794 = v1793 >= 12;	// L2792
    if (v1794) {	// L2793
      b_vld1 = 0;	// L2794
      int32_t v1795 = s21;	// L2795
      int32_t v1796 = v1795 & 3;	// L2796
      int v1797 = v1796;	// L2797
      uint8_t v1798 = hold_cnt1[v1797];	// L2798
      int32_t v1799 = v1798;	// L2799
      bool v1800 = v1799 > 0;	// L2800
      if (v1800) {	// L2801
        b_vld1 = 1;	// L2802
      }
    }
    int32_t v1801 = s11;	// L2805
    bool v1802 = v1801 < 8;	// L2806
    int32_t v1803 = dsmask1;	// L2807
    int32_t v1804 = v1803 >> v1801;	// L2809
    int32_t v1805 = v1804 & 1;	// L2810
    bool v1806 = v1805 == 1;	// L2811
    bool v1807 = v1802 & v1806;	// L2812
    if (v1807) {	// L2813
      int32_t v1808 = s11;	// L2814
      int v1809 = v1808;	// L2815
      int32_t v1810 = drf_full1[v1809];	// L2816
      bool v1811 = v1810 == 0;	// L2817
      if (v1811) {	// L2818
        a_vld1 = 0;	// L2819
      }
    }
    int32_t v1812 = s21;	// L2822
    bool v1813 = v1812 < 8;	// L2823
    int32_t v1814 = dsmask1;	// L2824
    int32_t v1815 = v1814 >> v1812;	// L2826
    int32_t v1816 = v1815 & 1;	// L2827
    bool v1817 = v1816 == 1;	// L2828
    bool v1818 = v1813 & v1817;	// L2829
    if (v1818) {	// L2830
      int32_t v1819 = s21;	// L2831
      int v1820 = v1819;	// L2832
      int32_t v1821 = drf_full1[v1820];	// L2833
      bool v1822 = v1821 == 0;	// L2834
      if (v1822) {	// L2835
        b_vld1 = 0;	// L2836
      }
    }
    int32_t binop1;	// L2839
    binop1 = 0;	// L2840
    int32_t v1824 = op1;	// L2841
    bool v1825 = v1824 == 0;	// L2842
    bool v1826 = v1824 == 1;	// L2844
    bool v1827 = v1824 == 2;	// L2846
    bool v1828 = v1824 == 8;	// L2848
    bool v1829 = v1824 == 9;	// L2850
    bool v1830 = v1825 | v1826;	// L2851
    bool v1831 = v1830 | v1827;	// L2852
    bool v1832 = v1831 | v1828;	// L2853
    bool v1833 = v1832 | v1829;	// L2854
    if (v1833) {	// L2855
      binop1 = 1;	// L2856
    }
    int32_t raw1;	// L2858
    raw1 = 0;	// L2859
    int32_t cmp_busy1;	// L2860
    cmp_busy1 = 0;	// L2861
    int32_t fwd_a1;	// L2862
    fwd_a1 = 0;	// L2863
    int32_t fwd_a_ix1;	// L2864
    fwd_a_ix1 = 0;	// L2865
    int32_t raw_a1;	// L2866
    raw_a1 = 0;	// L2867
    int32_t fwd_b1;	// L2868
    fwd_b1 = 0;	// L2869
    int32_t fwd_b_ix1;	// L2870
    fwd_b_ix1 = 0;	// L2871
    int32_t raw_b1;	// L2872
    raw_b1 = 0;	// L2873
    l_S_k_6_k2: for (int k2 = 0; k2 < 4; k2++) {	// L2874
      ac_int<34, true> v1843 = k2;	// L2875
      ac_int<34, true> v1844 = v1843 + 1;	// L2876
      int32_t v1845 = v1844;	// L2877
      int32_t kk1;	// L2878
      kk1 = v1845;	// L2879
      int32_t v1847 = kk1;	// L2880
      ac_int<34, true> v1848 = v1847;	// L2881
      ac_int<34, true> v1849 = 4 - v1848;	// L2882
      int32_t v1850 = v1849;	// L2883
      int32_t inflight1;	// L2884
      inflight1 = v1850;	// L2885
      int32_t need1;	// L2886
      need1 = 0;	// L2887
      int32_t v1853 = kk1;	// L2888
      int v1854 = v1853;	// L2889
      uint8_t v1855 = sb_long1[v1854];	// L2890
      int32_t v1856 = v1855;	// L2891
      bool v1857 = v1856 == 1;	// L2892
      if (v1857) {	// L2893
        need1 = 1;	// L2894
      }
      int32_t rdy1;	// L2896
      rdy1 = 0;	// L2897
      int32_t v1859 = inflight1;	// L2898
      int32_t v1860 = need1;	// L2899
      bool v1861 = v1859 >= v1860;	// L2900
      if (v1861) {	// L2901
        rdy1 = 1;	// L2902
      }
      int32_t v1862 = kk1;	// L2904
      int v1863 = v1862;	// L2905
      uint8_t v1864 = sb_v1[v1863];	// L2906
      int32_t v1865 = v1864;	// L2907
      bool v1866 = v1865 == 1;	// L2908
      uint8_t v1867 = sb_rtr1[v1863];	// L2911
      int32_t v1868 = v1867;	// L2912
      bool v1869 = v1868 == 0;	// L2913
      uint8_t v1870 = sb_dst1[v1863];	// L2916
      int32_t v1871 = v1870;	// L2917
      bool v1872 = v1871 < 12;	// L2918
      bool v1873 = v1866 & v1869;	// L2919
      bool v1874 = v1873 & v1872;	// L2920
      if (v1874) {	// L2921
        int32_t v1875 = s11;	// L2922
        bool v1876 = v1875 < 12;	// L2923
        int32_t v1877 = kk1;	// L2924
        int v1878 = v1877;	// L2925
        uint8_t v1879 = sb_dst1[v1878];	// L2926
        int32_t v1880 = v1879;	// L2927
        int32_t v1881 = v1880 & 7;	// L2928
        int32_t v1882 = v1875 & 7;	// L2930
        bool v1883 = v1881 == v1882;	// L2931
        bool v1884 = v1876 & v1883;	// L2932
        if (v1884) {	// L2933
          int32_t v1885 = rdy1;	// L2934
          bool v1886 = v1885 == 1;	// L2935
          if (v1886) {	// L2936
            fwd_a1 = 1;	// L2937
            int32_t v1887 = kk1;	// L2938
            int v1888 = v1887;	// L2939
            uint8_t v1889 = sb_ix1[v1888];	// L2940
            int32_t v1890 = v1889;	// L2941
            fwd_a_ix1 = v1890;	// L2942
            raw_a1 = 0;	// L2943
          } else {
            fwd_a1 = 0;	// L2945
            raw_a1 = 1;	// L2946
          }
        }
        int32_t v1891 = binop1;	// L2949
        bool v1892 = v1891 == 1;	// L2950
        int32_t v1893 = s21;	// L2951
        bool v1894 = v1893 < 12;	// L2952
        int32_t v1895 = kk1;	// L2953
        int v1896 = v1895;	// L2954
        uint8_t v1897 = sb_dst1[v1896];	// L2955
        int32_t v1898 = v1897;	// L2956
        int32_t v1899 = v1898 & 7;	// L2957
        int32_t v1900 = v1893 & 7;	// L2959
        bool v1901 = v1899 == v1900;	// L2960
        bool v1902 = v1892 & v1894;	// L2961
        bool v1903 = v1902 & v1901;	// L2962
        if (v1903) {	// L2963
          int32_t v1904 = rdy1;	// L2964
          bool v1905 = v1904 == 1;	// L2965
          if (v1905) {	// L2966
            fwd_b1 = 1;	// L2967
            int32_t v1906 = kk1;	// L2968
            int v1907 = v1906;	// L2969
            uint8_t v1908 = sb_ix1[v1907];	// L2970
            int32_t v1909 = v1908;	// L2971
            fwd_b_ix1 = v1909;	// L2972
            raw_b1 = 0;	// L2973
          } else {
            fwd_b1 = 0;	// L2975
            raw_b1 = 1;	// L2976
          }
        }
      }
      int32_t v1910 = kk1;	// L2980
      int v1911 = v1910;	// L2981
      uint8_t v1912 = sb_v1[v1911];	// L2982
      int32_t v1913 = v1912;	// L2983
      bool v1914 = v1913 == 1;	// L2984
      uint8_t v1915 = sb_cmp1[v1911];	// L2987
      int32_t v1916 = v1915;	// L2988
      bool v1917 = v1916 == 1;	// L2989
      bool v1918 = v1914 & v1917;	// L2990
      if (v1918) {	// L2991
        cmp_busy1 = 1;	// L2992
      }
    }
    int32_t v1919 = raw_a1;	// L2995
    raw1 = v1919;	// L2996
    int32_t v1920 = binop1;	// L2997
    bool v1921 = v1920 == 1;	// L2998
    int32_t v1922 = raw_b1;	// L2999
    bool v1923 = v1922 == 1;	// L3000
    bool v1924 = v1921 & v1923;	// L3001
    if (v1924) {	// L3002
      raw1 = 1;	// L3003
    }
    int32_t v1925 = fwd_a1;	// L3005
    bool v1926 = v1925 == 1;	// L3006
    if (v1926) {	// L3007
      int32_t v1927 = fwd_a_ix1;	// L3008
      int v1928 = v1927;	// L3009
      half v1929 = resq1[v1928];	// L3010
      a1 = v1929;	// L3011
      a_vld1 = 1;	// L3012
    }
    int32_t v1930 = fwd_b1;	// L3014
    bool v1931 = v1930 == 1;	// L3015
    if (v1931) {	// L3016
      int32_t v1932 = fwd_b_ix1;	// L3017
      int v1933 = v1932;	// L3018
      half v1934 = resq1[v1933];	// L3019
      b1 = v1934;	// L3020
      b_vld1 = 1;	// L3021
    }
    int32_t is_cond1;	// L3023
    is_cond1 = 0;	// L3024
    int32_t v1936 = op1;	// L3025
    bool v1937 = v1936 >= 12;	// L3026
    ac_int<33, true> v1938 = v1936;	// L3028
    bool v1939 = v1938 <= 15;	// L3029
    bool v1940 = v1937 & v1939;	// L3030
    if (v1940) {	// L3031
      is_cond1 = 1;	// L3032
    }
    int32_t grant1;	// L3034
    grant1 = 0;	// L3035
    int32_t v1942 = pc1;	// L3036
    bool v1943 = v1942 >= 0;	// L3037
    if (v1943) {	// L3038
      grant1 = 1;	// L3039
    }
    int32_t v1944 = pc1;	// L3041
    bool v1945 = v1944 >= 0;	// L3042
    int32_t v1946 = a_vld1;	// L3043
    bool v1947 = v1946 == 0;	// L3044
    int32_t v1948 = binop1;	// L3045
    bool v1949 = v1948 == 1;	// L3046
    int32_t v1950 = b_vld1;	// L3047
    bool v1951 = v1950 == 0;	// L3048
    bool v1952 = v1949 & v1951;	// L3049
    bool v1953 = v1947 | v1952;	// L3050
    bool v1954 = v1945 & v1953;	// L3051
    if (v1954) {	// L3052
      grant1 = 0;	// L3053
    }
    int32_t v1955 = pc1;	// L3055
    bool v1956 = v1955 >= 0;	// L3056
    int32_t v1957 = raw1;	// L3057
    bool v1958 = v1957 == 1;	// L3058
    int32_t v1959 = is_cond1;	// L3059
    bool v1960 = v1959 == 1;	// L3060
    int32_t v1961 = cmp_busy1;	// L3061
    bool v1962 = v1961 == 1;	// L3062
    bool v1963 = v1960 & v1962;	// L3063
    bool v1964 = v1958 | v1963;	// L3064
    bool v1965 = v1956 & v1964;	// L3065
    if (v1965) {	// L3066
      grant1 = 0;	// L3067
    }
    int32_t v1966 = retire_ok1;	// L3069
    bool v1967 = v1966 == 0;	// L3070
    if (v1967) {	// L3071
      grant1 = 0;	// L3072
    }
    int32_t v1968 = grant1;	// L3074
    bool v1969 = v1968 == 1;	// L3075
    if (v1969) {	// L3076
      int8_t v1970 = instr_cnt1;	// L3077
      int32_t v1971 = cfg_isz1;	// L3078
      int32_t v1972 = v1970;	// L3079
      bool v1973 = v1972 == v1971;	// L3080
      if (v1973) {	// L3081
        instr_cnt1 = 0;	// L3082
        int8_t v1974 = iter_cnt1;	// L3083
        int32_t v1975 = cfg_itsz1;	// L3084
        ac_int<33, true> v1976 = v1975;	// L3085
        ac_int<33, true> v1977 = v1976 - 1;	// L3086
        ac_int<33, true> v1978 = v1974;	// L3087
        bool v1979 = v1978 == v1977;	// L3088
        if (v1979) {	// L3089
          fetch_en1 = 0;	// L3090
        } else {
          int8_t v1980 = iter_cnt1;	// L3092
          ac_int<33, true> v1981 = v1980;	// L3093
          ac_int<33, true> v1982 = v1981 + 1;	// L3094
          uint8_t v1983 = v1982;	// L3095
          iter_cnt1 = v1983;	// L3096
        }
      } else {
        int8_t v1984 = instr_cnt1;	// L3099
        ac_int<33, true> v1985 = v1984;	// L3100
        ac_int<33, true> v1986 = v1985 + 1;	// L3101
        uint8_t v1987 = v1986;	// L3102
        instr_cnt1 = v1987;	// L3103
      }
    }
    int32_t c11;	// L3106
    c11 = -1;	// L3107
    int32_t c21;	// L3108
    c21 = -1;	// L3109
    int32_t v1990 = grant1;	// L3110
    bool v1991 = v1990 == 1;	// L3111
    int32_t v1992 = s11;	// L3112
    bool v1993 = v1992 >= 12;	// L3113
    bool v1994 = v1991 & v1993;	// L3114
    if (v1994) {	// L3115
      int32_t v1995 = s11;	// L3116
      int32_t v1996 = v1995 & 3;	// L3117
      c11 = v1996;	// L3118
    }
    int32_t v1997 = grant1;	// L3120
    bool v1998 = v1997 == 1;	// L3121
    int32_t v1999 = s21;	// L3122
    bool v2000 = v1999 >= 12;	// L3123
    bool v2001 = v1998 & v2000;	// L3124
    if (v2001) {	// L3125
      int32_t v2002 = s21;	// L3126
      int32_t v2003 = v2002 & 3;	// L3127
      c21 = v2003;	// L3128
    }
    int32_t v2004 = c11;	// L3130
    bool v2005 = v2004 >= 0;	// L3131
    if (v2005) {	// L3132
      int32_t v2006 = c11;	// L3133
      int v2007 = v2006;	// L3134
      half v2008 = hold_v1[v2007][1];	// L3135
      hold_v1[v2007][0] = v2008;	// L3138
      int32_t v2009 = c11;	// L3139
      int v2010 = v2009;	// L3140
      uint8_t v2011 = hold_cnt1[v2010];	// L3141
      ac_int<33, true> v2012 = v2011;	// L3142
      ac_int<33, true> v2013 = v2012 - 1;	// L3143
      uint8_t v2014 = v2013;	// L3144
      hold_cnt1[v2010] = v2014;	// L3147
    }
    int32_t v2015 = c21;	// L3149
    bool v2016 = v2015 >= 0;	// L3150
    int32_t v2017 = c11;	// L3152
    bool v2018 = v2015 != v2017;	// L3153
    bool v2019 = v2016 & v2018;	// L3154
    if (v2019) {	// L3155
      int32_t v2020 = c21;	// L3156
      int v2021 = v2020;	// L3157
      half v2022 = hold_v1[v2021][1];	// L3158
      hold_v1[v2021][0] = v2022;	// L3161
      int32_t v2023 = c21;	// L3162
      int v2024 = v2023;	// L3163
      uint8_t v2025 = hold_cnt1[v2024];	// L3164
      ac_int<33, true> v2026 = v2025;	// L3165
      ac_int<33, true> v2027 = v2026 - 1;	// L3166
      uint8_t v2028 = v2027;	// L3167
      hold_cnt1[v2024] = v2028;	// L3170
    }
    l_S_d_7_d9: for (int d9 = 0; d9 < 4; d9++) {	// L3172
      sc_r1[d9] = 0;	// L3173
    }
    int32_t v2030 = c11;	// L3175
    bool v2031 = v2030 >= 0;	// L3176
    if (v2031) {	// L3177
      int32_t v2032 = c11;	// L3178
      int v2033 = v2032;	// L3179
      sc_r1[v2033] = 1;	// L3180
    }
    int32_t v2034 = c21;	// L3182
    bool v2035 = v2034 >= 0;	// L3183
    int32_t v2036 = c11;	// L3185
    bool v2037 = v2034 != v2036;	// L3186
    bool v2038 = v2035 & v2037;	// L3187
    if (v2038) {	// L3188
      int32_t v2039 = c21;	// L3189
      int v2040 = v2039;	// L3190
      sc_r1[v2040] = 1;	// L3191
    }
    int32_t v2041 = grant1;	// L3193
    bool v2042 = v2041 == 1;	// L3194
    int32_t v2043 = s11;	// L3195
    bool v2044 = v2043 < 8;	// L3196
    int32_t v2045 = dsmask1;	// L3197
    int32_t v2046 = v2045 >> v2043;	// L3199
    int32_t v2047 = v2046 & 1;	// L3200
    bool v2048 = v2047 == 1;	// L3201
    bool v2049 = v2042 & v2044;	// L3202
    bool v2050 = v2049 & v2048;	// L3203
    if (v2050) {	// L3204
      int32_t v2051 = s11;	// L3205
      int v2052 = v2051;	// L3206
      drf_full1[v2052] = 0;	// L3207
    }
    int32_t v2053 = grant1;	// L3209
    bool v2054 = v2053 == 1;	// L3210
    int32_t v2055 = s21;	// L3211
    bool v2056 = v2055 < 8;	// L3212
    int32_t v2057 = dsmask1;	// L3213
    int32_t v2058 = v2057 >> v2055;	// L3215
    int32_t v2059 = v2058 & 1;	// L3216
    bool v2060 = v2059 == 1;	// L3217
    bool v2061 = v2054 & v2056;	// L3218
    bool v2062 = v2061 & v2060;	// L3219
    if (v2062) {	// L3220
      int32_t v2063 = s21;	// L3221
      int v2064 = v2063;	// L3222
      drf_full1[v2064] = 0;	// L3223
    }
    half res1;	// L3225
    res1 = (double)0.000000;	// L3226
    int32_t v2066 = op1;	// L3227
    bool v2067 = v2066 == 0;	// L3228
    if (v2067) {	// L3229
      half v2068 = a1;	// L3230
      half v2069 = b1;	// L3231
      half v2070 = v2068 + v2069;	// L3232
      res1 = v2070;	// L3233
    } else {
      int32_t v2071 = op1;	// L3235
      bool v2072 = v2071 == 1;	// L3236
      if (v2072) {	// L3237
        half v2073 = a1;	// L3238
        half v2074 = b1;	// L3239
        half v2075 = v2073 - v2074;	// L3240
        res1 = v2075;	// L3241
      } else {
        int32_t v2076 = op1;	// L3243
        bool v2077 = v2076 == 2;	// L3244
        if (v2077) {	// L3245
          half v2078 = a1;	// L3246
          half v2079 = b1;	// L3247
          half v2080 = v2078 * v2079;	// L3248
          res1 = v2080;	// L3249
        } else {
          int32_t v2081 = op1;	// L3251
          bool v2082 = v2081 == 8;	// L3252
          if (v2082) {	// L3253
            half v2083 = a1;	// L3254
            half v2084 = b1;	// L3255
            bool v2085 = v2083 >= v2084;	// L3256
            if (v2085) {	// L3257
              res1 = (double)1.000000;	// L3258
            } else {
              res1 = (double)-1.000000;	// L3260
            }
          } else {
            int32_t v2086 = op1;	// L3263
            bool v2087 = v2086 == 9;	// L3264
            if (v2087) {	// L3265
              half v2088 = a1;	// L3266
              half v2089 = b1;	// L3267
              bool v2090 = v2088 < v2089;	// L3268
              if (v2090) {	// L3269
                res1 = (double)1.000000;	// L3270
              } else {
                res1 = (double)-1.000000;	// L3272
              }
            } else {
              half v2091 = a1;	// L3275
              res1 = v2091;	// L3276
            }
          }
        }
      }
    }
    int32_t v2092 = a_vld1;	// L3282
    int32_t res_vld1;	// L3283
    res_vld1 = v2092;	// L3284
    int32_t v2094 = op1;	// L3285
    bool v2095 = v2094 == 0;	// L3286
    bool v2096 = v2094 == 1;	// L3288
    bool v2097 = v2094 == 2;	// L3290
    bool v2098 = v2094 == 8;	// L3292
    bool v2099 = v2094 == 9;	// L3294
    bool v2100 = v2095 | v2096;	// L3295
    bool v2101 = v2100 | v2097;	// L3296
    bool v2102 = v2101 | v2098;	// L3297
    bool v2103 = v2102 | v2099;	// L3298
    if (v2103) {	// L3299
      int32_t v2104 = a_vld1;	// L3300
      int32_t v2105 = b_vld1;	// L3301
      int64_t v2106 = v2104;	// L3302
      int64_t v2107 = v2105;	// L3303
      int64_t v2108 = v2106 * v2107;	// L3304
      int32_t v2109 = v2108;	// L3305
      res_vld1 = v2109;	// L3306
    }
    int32_t v2110 = grant1;	// L3308
    bool v2111 = v2110 == 0;	// L3309
    if (v2111) {	// L3310
      res_vld1 = 0;	// L3311
    }
    int32_t is_rtr1;	// L3313
    is_rtr1 = 0;	// L3314
    int32_t v2113 = op1;	// L3315
    bool v2114 = v2113 >= 4;	// L3316
    ac_int<33, true> v2115 = v2113;	// L3318
    bool v2116 = v2115 <= 7;	// L3319
    bool v2117 = v2114 & v2116;	// L3320
    if (v2117) {	// L3321
      is_rtr1 = 1;	// L3322
    }
    int32_t v2118 = retire_ok1;	// L3324
    bool v2119 = v2118 == 1;	// L3325
    if (v2119) {	// L3326
      l_S_k_8_k3: for (int k3 = 0; k3 < 4; k3++) {	// L3327
        uint8_t v2121 = sb_v1[(k3 + 1)];	// L3328
        sb_v1[k3] = v2121;	// L3329
        uint8_t v2122 = sb_dst1[(k3 + 1)];	// L3330
        sb_dst1[k3] = v2122;	// L3331
        uint8_t v2123 = sb_cmp1[(k3 + 1)];	// L3332
        sb_cmp1[k3] = v2123;	// L3333
        uint8_t v2124 = sb_rtr1[(k3 + 1)];	// L3334
        sb_rtr1[k3] = v2124;	// L3335
        uint8_t v2125 = sb_inj1[(k3 + 1)];	// L3336
        sb_inj1[k3] = v2125;	// L3337
        uint8_t v2126 = sb_dir1[(k3 + 1)];	// L3338
        sb_dir1[k3] = v2126;	// L3339
        uint8_t v2127 = sb_id1[(k3 + 1)];	// L3340
        sb_id1[k3] = v2127;	// L3341
        uint8_t v2128 = sb_rvld1[(k3 + 1)];	// L3342
        sb_rvld1[k3] = v2128;	// L3343
        uint8_t v2129 = sb_ix1[(k3 + 1)];	// L3344
        sb_ix1[k3] = v2129;	// L3345
        uint8_t v2130 = sb_long1[(k3 + 1)];	// L3346
        sb_long1[k3] = v2130;	// L3347
      }
      sb_v1[4] = 0;	// L3349
    }
    int32_t v2131 = grant1;	// L3351
    bool v2132 = v2131 == 1;	// L3352
    if (v2132) {	// L3353
      half v2133 = res1;	// L3354
      int8_t v2134 = resq_wr1;	// L3355
      int v2135 = v2134;	// L3356
      resq1[v2135] = v2133;	// L3357
      int32_t cq1;	// L3358
      cq1 = 0;	// L3359
      int32_t v2137 = op1;	// L3360
      bool v2138 = v2137 == 8;	// L3361
      if (v2138) {	// L3362
        half v2139 = a1;	// L3363
        half v2140 = b1;	// L3364
        bool v2141 = v2139 >= v2140;	// L3365
        if (v2141) {	// L3366
          cq1 = 1;	// L3367
        }
      }
      int32_t v2142 = op1;	// L3370
      bool v2143 = v2142 == 9;	// L3371
      if (v2143) {	// L3372
        half v2144 = a1;	// L3373
        half v2145 = b1;	// L3374
        bool v2146 = v2144 < v2145;	// L3375
        if (v2146) {	// L3376
          cq1 = 1;	// L3377
        }
      }
      int32_t v2147 = cq1;	// L3380
      uint8_t v2148 = v2147;	// L3381
      int8_t v2149 = resq_wr1;	// L3382
      int v2150 = v2149;	// L3383
      cmpq1[v2150] = v2148;	// L3384
      sb_v1[4] = 1;	// L3385
      int32_t v2151 = dst1;	// L3386
      uint8_t v2152 = v2151;	// L3387
      sb_dst1[4] = v2152;	// L3388
      int8_t v2153 = resq_wr1;	// L3389
      sb_ix1[4] = v2153;	// L3390
      int32_t v2154 = binop1;	// L3391
      uint8_t v2155 = v2154;	// L3392
      sb_long1[4] = v2155;	// L3393
      sb_cmp1[4] = 0;	// L3394
      int32_t v2156 = op1;	// L3395
      bool v2157 = v2156 == 8;	// L3396
      bool v2158 = v2156 == 9;	// L3398
      bool v2159 = v2157 | v2158;	// L3399
      if (v2159) {	// L3400
        sb_cmp1[4] = 1;	// L3401
      }
      int32_t v2160 = is_rtr1;	// L3403
      int32_t rtrf1;	// L3404
      rtrf1 = v2160;	// L3405
      int32_t v2162 = is_cond1;	// L3406
      bool v2163 = v2162 == 1;	// L3407
      if (v2163) {	// L3408
        rtrf1 = 1;	// L3409
      }
      int32_t v2164 = rtrf1;	// L3411
      uint8_t v2165 = v2164;	// L3412
      sb_rtr1[4] = v2165;	// L3413
      int32_t v2166 = is_rtr1;	// L3414
      int32_t inj1;	// L3415
      inj1 = v2166;	// L3416
      int32_t v2168 = is_cond1;	// L3417
      bool v2169 = v2168 == 1;	// L3418
      int8_t v2170 = condition_reg1;	// L3419
      int32_t v2171 = v2170;	// L3420
      bool v2172 = v2171 == 1;	// L3421
      bool v2173 = v2169 & v2172;	// L3422
      if (v2173) {	// L3423
        inj1 = 1;	// L3424
      }
      int32_t v2174 = inj1;	// L3426
      uint8_t v2175 = v2174;	// L3427
      sb_inj1[4] = v2175;	// L3428
      int32_t v2176 = op1;	// L3429
      int32_t v2177 = v2176 & 3;	// L3430
      uint8_t v2178 = v2177;	// L3431
      sb_dir1[4] = v2178;	// L3432
      int32_t v2179 = s21;	// L3433
      uint8_t v2180 = v2179;	// L3434
      sb_id1[4] = v2180;	// L3435
      int32_t v2181 = res_vld1;	// L3436
      uint8_t v2182 = v2181;	// L3437
      sb_rvld1[4] = v2182;	// L3438
      int8_t v2183 = resq_wr1;	// L3439
      ac_int<33, true> v2184 = v2183;	// L3440
      ac_int<33, true> v2185 = v2184 + 1;	// L3441
      ac_int<33, true> v2186 = v2185 & 7;	// L3442
      uint8_t v2187 = v2186;	// L3443
      resq_wr1 = v2187;	// L3444
    }
    txn_r1 = 0;	// L3446
    txs_r1 = 0;	// L3447
    txw_r1 = 0;	// L3448
    txe_r1 = 0;	// L3449
    int32_t v2188 = txp_v1[0];	// L3450
    bool v2189 = v2188 == 1;	// L3451
    int32_t v2190 = scred1[0];	// L3452
    bool v2191 = v2190 > 0;	// L3453
    bool v2192 = v2189 & v2191;	// L3454
    if (v2192) {	// L3455
      ac_int<17, false> twn1;	// L3456
      twn1 = 0;	// L3457
      ac_int<17, true> v2194 = twn1;	// L3458
      ac_int<17, true> v2195;
      ap_int<17> v2195_tmp = v2194;
      v2195_tmp[0] = 1;      v2195 = v2195_tmp;	// L3459
      twn1 = v2195;	// L3460
      half v2196 = txp_d1[0];	// L3461
      uint16_t v2197;
      union { half from; uint16_t to;} _converter_v2196_to_v2197 = {};
      _converter_v2196_to_v2197.from = v2196;
      v2197 = _converter_v2196_to_v2197.to;	// L3462
      ac_int<17, true> v2198 = twn1;	// L3463
      ac_int<17, true> v2199;
      ap_int<17> v2199_tmp = v2198;
      v2199_tmp(16, 1) = v2197;
      v2199 = v2199_tmp;	// L3464
      twn1 = v2199;	// L3465
      ac_int<17, true> v2200 = twn1;	// L3466
      txn_r1 = v2200;	// L3467
      txp_v1[0] = 0;	// L3468
      int32_t v2201 = scred1[0];	// L3469
      ac_int<33, true> v2202 = v2201;	// L3470
      ac_int<33, true> v2203 = v2202 - 1;	// L3471
      int32_t v2204 = v2203;	// L3472
      scred1[0] = v2204;	// L3473
    }
    int32_t v2205 = txp_v1[1];	// L3475
    bool v2206 = v2205 == 1;	// L3476
    int32_t v2207 = scred1[1];	// L3477
    bool v2208 = v2207 > 0;	// L3478
    bool v2209 = v2206 & v2208;	// L3479
    if (v2209) {	// L3480
      ac_int<17, false> tws1;	// L3481
      tws1 = 0;	// L3482
      ac_int<17, true> v2211 = tws1;	// L3483
      ac_int<17, true> v2212;
      ap_int<17> v2212_tmp = v2211;
      v2212_tmp[0] = 1;      v2212 = v2212_tmp;	// L3484
      tws1 = v2212;	// L3485
      half v2213 = txp_d1[1];	// L3486
      uint16_t v2214;
      union { half from; uint16_t to;} _converter_v2213_to_v2214 = {};
      _converter_v2213_to_v2214.from = v2213;
      v2214 = _converter_v2213_to_v2214.to;	// L3487
      ac_int<17, true> v2215 = tws1;	// L3488
      ac_int<17, true> v2216;
      ap_int<17> v2216_tmp = v2215;
      v2216_tmp(16, 1) = v2214;
      v2216 = v2216_tmp;	// L3489
      tws1 = v2216;	// L3490
      ac_int<17, true> v2217 = tws1;	// L3491
      txs_r1 = v2217;	// L3492
      txp_v1[1] = 0;	// L3493
      int32_t v2218 = scred1[1];	// L3494
      ac_int<33, true> v2219 = v2218;	// L3495
      ac_int<33, true> v2220 = v2219 - 1;	// L3496
      int32_t v2221 = v2220;	// L3497
      scred1[1] = v2221;	// L3498
    }
    int32_t v2222 = txp_v1[2];	// L3500
    bool v2223 = v2222 == 1;	// L3501
    int32_t v2224 = scred1[2];	// L3502
    bool v2225 = v2224 > 0;	// L3503
    bool v2226 = v2223 & v2225;	// L3504
    if (v2226) {	// L3505
      ac_int<17, false> tww1;	// L3506
      tww1 = 0;	// L3507
      ac_int<17, true> v2228 = tww1;	// L3508
      ac_int<17, true> v2229;
      ap_int<17> v2229_tmp = v2228;
      v2229_tmp[0] = 1;      v2229 = v2229_tmp;	// L3509
      tww1 = v2229;	// L3510
      half v2230 = txp_d1[2];	// L3511
      uint16_t v2231;
      union { half from; uint16_t to;} _converter_v2230_to_v2231 = {};
      _converter_v2230_to_v2231.from = v2230;
      v2231 = _converter_v2230_to_v2231.to;	// L3512
      ac_int<17, true> v2232 = tww1;	// L3513
      ac_int<17, true> v2233;
      ap_int<17> v2233_tmp = v2232;
      v2233_tmp(16, 1) = v2231;
      v2233 = v2233_tmp;	// L3514
      tww1 = v2233;	// L3515
      ac_int<17, true> v2234 = tww1;	// L3516
      txw_r1 = v2234;	// L3517
      txp_v1[2] = 0;	// L3518
      int32_t v2235 = scred1[2];	// L3519
      ac_int<33, true> v2236 = v2235;	// L3520
      ac_int<33, true> v2237 = v2236 - 1;	// L3521
      int32_t v2238 = v2237;	// L3522
      scred1[2] = v2238;	// L3523
    }
    int32_t v2239 = txp_v1[3];	// L3525
    bool v2240 = v2239 == 1;	// L3526
    int32_t v2241 = scred1[3];	// L3527
    bool v2242 = v2241 > 0;	// L3528
    bool v2243 = v2240 & v2242;	// L3529
    if (v2243) {	// L3530
      ac_int<17, false> twe1;	// L3531
      twe1 = 0;	// L3532
      ac_int<17, true> v2245 = twe1;	// L3533
      ac_int<17, true> v2246;
      ap_int<17> v2246_tmp = v2245;
      v2246_tmp[0] = 1;      v2246 = v2246_tmp;	// L3534
      twe1 = v2246;	// L3535
      half v2247 = txp_d1[3];	// L3536
      uint16_t v2248;
      union { half from; uint16_t to;} _converter_v2247_to_v2248 = {};
      _converter_v2247_to_v2248.from = v2247;
      v2248 = _converter_v2247_to_v2248.to;	// L3537
      ac_int<17, true> v2249 = twe1;	// L3538
      ac_int<17, true> v2250;
      ap_int<17> v2250_tmp = v2249;
      v2250_tmp(16, 1) = v2248;
      v2250 = v2250_tmp;	// L3539
      twe1 = v2250;	// L3540
      ac_int<17, true> v2251 = twe1;	// L3541
      txe_r1 = v2251;	// L3542
      txp_v1[3] = 0;	// L3543
      int32_t v2252 = scred1[3];	// L3544
      ac_int<33, true> v2253 = v2252;	// L3545
      ac_int<33, true> v2254 = v2253 - 1;	// L3546
      int32_t v2255 = v2254;	// L3547
      scred1[3] = v2255;	// L3548
    }
    int32_t v2256 = crv_vld1;	// L3550
    bool v2257 = v2256 == 1;	// L3551
    if (v2257) {	// L3552
      int32_t v2258 = crv_mode1;	// L3553
      bool v2259 = v2258 == 1;	// L3554
      if (v2259) {	// L3555
        int32_t v2260 = crv_addr1;	// L3556
        int32_t v2261 = v2260 >> 3;	// L3557
        int32_t v2262 = v2261 & 1;	// L3558
        bool v2263 = v2262 == 1;	// L3559
        if (v2263) {	// L3560
          int32_t v2264 = crv_raw1;	// L3561
          int32_t v2265 = crv_addr1;	// L3562
          int32_t v2266 = v2265 & 7;	// L3563
          int v2267 = v2266;	// L3564
          irf1[v2267] = v2264;	// L3565
        } else {
          int32_t v2268 = crv_addr1;	// L3567
          bool v2269 = v2268 == 0;	// L3568
          if (v2269) {	// L3569
            int32_t v2270 = crv_raw1;	// L3570
            int32_t v2271 = v2270 & 255;	// L3571
            dsmask1 = v2271;	// L3572
            int32_t v2272 = crv_raw1;	// L3573
            int32_t v2273 = v2272 >> 8;	// L3574
            int32_t v2274 = v2273 & 7;	// L3575
            cfg_isz1 = v2274;	// L3576
            int32_t v2275 = crv_raw1;	// L3577
            int32_t v2276 = v2275 >> 15;	// L3578
            int32_t v2277 = v2276 & 1;	// L3579
            bool v2278 = v2277 == 1;	// L3580
            if (v2278) {	// L3581
              fetch_en1 = 1;	// L3582
              instr_cnt1 = 0;	// L3583
              iter_cnt1 = 0;	// L3584
            }
          } else {
            int32_t v2279 = crv_addr1;	// L3587
            bool v2280 = v2279 == 1;	// L3588
            if (v2280) {	// L3589
              int32_t v2281 = crv_raw1;	// L3590
              int32_t v2282 = v2281 & 255;	// L3591
              cfg_itsz1 = v2282;	// L3592
            }
          }
        }
      } else {
        int32_t v2283 = crv_addr1;	// L3597
        int32_t v2284 = v2283 >> 2;	// L3598
        int32_t v2285 = v2284 & 3;	// L3599
        bool v2286 = v2285 == 3;	// L3600
        if (v2286) {	// L3601
          int32_t v2287 = crv_addr1;	// L3602
          int32_t v2288 = v2287 & 3;	// L3603
          int v2289 = v2288;	// L3604
          txp_v1[v2289] = 1;	// L3605
          half v2290 = crv_data1;	// L3606
          int32_t v2291 = crv_addr1;	// L3607
          int32_t v2292 = v2291 & 3;	// L3608
          int v2293 = v2292;	// L3609
          txp_d1[v2293] = v2290;	// L3610
          int32_t v2294 = crv_addr1;	// L3611
          int32_t v2295 = v2294 & 3;	// L3612
          int v2296 = v2295;	// L3613
          txp_r1[v2296] = 1;	// L3614
        } else {
          int32_t v2297 = crv_addr1;	// L3616
          bool v2298 = v2297 < 8;	// L3617
          int32_t v2299 = dsmask1;	// L3618
          int32_t v2300 = v2299 >> v2297;	// L3620
          int32_t v2301 = v2300 & 1;	// L3621
          bool v2302 = v2301 == 1;	// L3622
          bool v2303 = v2298 & v2302;	// L3623
          if (v2303) {	// L3624
            int32_t v2304 = crv_addr1;	// L3625
            int v2305 = v2304;	// L3626
            int32_t v2306 = drf_full1[v2305];	// L3627
            bool v2307 = v2306 == 0;	// L3628
            if (v2307) {	// L3629
              half v2308 = crv_data1;	// L3630
              int32_t v2309 = crv_addr1;	// L3631
              int v2310 = v2309;	// L3632
              drf1[v2310] = v2308;	// L3633
              int32_t v2311 = crv_addr1;	// L3634
              int v2312 = v2311;	// L3635
              drf_full1[v2312] = 1;	// L3636
            }
          } else {
            half v2313 = crv_data1;	// L3639
            int32_t v2314 = crv_addr1;	// L3640
            int v2315 = v2314;	// L3641
            drf1[v2315] = v2313;	// L3642
          }
        }
      }
    }
    ac_int<26, true> v2316 = oe_r1;	// L3647
    v1166.write(v2316);	// L3648
    ac_int<26, true> v2317 = ow_r1;	// L3649
    v1167.write(v2317);	// L3650
    ac_int<26, true> v2318 = os_r1;	// L3651
    v1168.write(v2318);	// L3652
    ac_int<26, true> v2319 = on_r1;	// L3653
    v1169.write(v2319);	// L3654
    ac_int<17, true> v2320 = txe_r1;	// L3655
    v1170.write(v2320);	// L3656
    ac_int<17, true> v2321 = txw_r1;	// L3657
    v1171.write(v2321);	// L3658
    ac_int<17, true> v2322 = txs_r1;	// L3659
    v1172.write(v2322);	// L3660
    ac_int<17, true> v2323 = txn_r1;	// L3661
    v1173.write(v2323);	// L3662
    int8_t v2324 = cre_r1;	// L3663
    v1174.write(v2324);	// L3664
    int8_t v2325 = crw_r1;	// L3665
    v1175.write(v2325);	// L3666
    int8_t v2326 = crs_r1;	// L3667
    v1176.write(v2326);	// L3668
    int8_t v2327 = crn_r1;	// L3669
    v1177.write(v2327);	// L3670
    int32_t v2328 = sc_r1[0];	// L3671
    v1180.write(v2328);	// L3672
    int32_t v2329 = sc_r1[1];	// L3673
    v1181.write(v2329);	// L3674
    int32_t v2330 = sc_r1[2];	// L3675
    v1178.write(v2330);	// L3676
    int32_t v2331 = sc_r1[3];	// L3677
    v1179.write(v2331);	// L3678
  }
}

void node_1_0(
  ac_channel< ac_int<26, false> >& v2332,
  ac_channel< ac_int<26, false> >& v2333,
  ac_channel< ac_int<26, false> >& v2334,
  ac_channel< ac_int<26, false> >& v2335,
  ac_channel< ac_int<17, false> >& v2336,
  ac_channel< ac_int<17, false> >& v2337,
  ac_channel< ac_int<17, false> >& v2338,
  ac_channel< ac_int<17, false> >& v2339,
  ac_channel< int32_t >& v2340,
  ac_channel< int32_t >& v2341,
  ac_channel< int32_t >& v2342,
  ac_channel< int32_t >& v2343,
  ac_channel< int32_t >& v2344,
  ac_channel< int32_t >& v2345,
  ac_channel< int32_t >& v2346,
  ac_channel< int32_t >& v2347,
  ac_channel< ac_int<26, false> >& v2348,
  ac_channel< ac_int<26, false> >& v2349,
  ac_channel< ac_int<26, false> >& v2350,
  ac_channel< ac_int<26, false> >& v2351,
  ac_channel< int32_t >& v2352,
  ac_channel< int32_t >& v2353,
  ac_channel< int32_t >& v2354,
  ac_channel< int32_t >& v2355,
  ac_channel< int32_t >& v2356,
  ac_channel< int32_t >& v2357,
  ac_channel< int32_t >& v2358,
  ac_channel< int32_t >& v2359,
  ac_channel< ac_int<17, false> >& v2360,
  ac_channel< ac_int<17, false> >& v2361,
  ac_channel< ac_int<17, false> >& v2362,
  ac_channel< ac_int<17, false> >& v2363
) {	// L3682
  int32_t irf2[8];	// L3719
  for (int v2365 = 0; v2365 < 8; v2365++) {	// L3720
    irf2[v2365] = 0;	// L3720
  }
  half drf2[8];	// L3721
  for (int v2367 = 0; v2367 < 8; v2367++) {	// L3722
    drf2[v2367] = (double)0.000000;	// L3722
  }
  int32_t drf_full2[8];	// L3723
  for (int v2369 = 0; v2369 < 8; v2369++) {	// L3724
    drf_full2[v2369] = 0;	// L3724
  }
  int32_t dsmask2;	// L3725
  dsmask2 = 0;	// L3726
  int32_t crv_vld2;	// L3727
  crv_vld2 = 0;	// L3728
  half crv_data2;	// L3729
  crv_data2 = (double)0.000000;	// L3730
  int32_t crv_addr2;	// L3731
  crv_addr2 = 0;	// L3732
  int32_t crv_mode2;	// L3733
  crv_mode2 = 0;	// L3734
  int32_t crv_raw2;	// L3735
  crv_raw2 = 0;	// L3736
  int32_t csd_vld2;	// L3737
  csd_vld2 = 0;	// L3738
  ac_int<26, false> csd_pkt2;	// L3739
  csd_pkt2 = 0;	// L3740
  int32_t csd_dir2;	// L3741
  csd_dir2 = 0;	// L3742
  int32_t row_id2;	// L3743
  row_id2 = 1;	// L3744
  int32_t col_id2;	// L3745
  col_id2 = 0;	// L3746
  ac_int<26, false> oe_r2;	// L3747
  oe_r2 = 0;	// L3748
  ac_int<26, false> ow_r2;	// L3749
  ow_r2 = 0;	// L3750
  ac_int<26, false> on_r2;	// L3751
  on_r2 = 0;	// L3752
  ac_int<26, false> os_r2;	// L3753
  os_r2 = 0;	// L3754
  ac_int<17, false> txn_r2;	// L3755
  txn_r2 = 0;	// L3756
  ac_int<17, false> txs_r2;	// L3757
  txs_r2 = 0;	// L3758
  ac_int<17, false> txw_r2;	// L3759
  txw_r2 = 0;	// L3760
  ac_int<17, false> txe_r2;	// L3761
  txe_r2 = 0;	// L3762
  half hold_v2[4][2];	// L3763
  for (int v2390 = 0; v2390 < 4; v2390++) {	// L3764
    for (int v2391 = 0; v2391 < 2; v2391++) {	// L3764
      hold_v2[v2390][v2391] = (double)0.000000;	// L3764
    }
  }
  uint8_t hold_cnt2[4];	// L3765
  for (int v2393 = 0; v2393 < 4; v2393++) {	// L3766
    hold_cnt2[v2393] = 0;	// L3766
  }
  ac_int<26, false> rbuf2[4][2];	// L3767
  for (int v2395 = 0; v2395 < 4; v2395++) {	// L3768
    for (int v2396 = 0; v2396 < 2; v2396++) {	// L3768
      rbuf2[v2395][v2396] = 0;	// L3768
    }
  }
  uint8_t rbcnt2[4];	// L3769
  for (int v2398 = 0; v2398 < 4; v2398++) {	// L3770
    rbcnt2[v2398] = 0;	// L3770
  }
  uint8_t rcred2[4];	// L3771
  for (int v2400 = 0; v2400 < 4; v2400++) {	// L3772
    rcred2[v2400] = 0;	// L3772
  }
  uint8_t cre_r2;	// L3773
  cre_r2 = 2;	// L3774
  uint8_t crw_r2;	// L3775
  crw_r2 = 2;	// L3776
  uint8_t crs_r2;	// L3777
  crs_r2 = 2;	// L3778
  uint8_t crn_r2;	// L3779
  crn_r2 = 2;	// L3780
  int32_t scred2[4];	// L3781
  for (int v2406 = 0; v2406 < 4; v2406++) {	// L3782
    scred2[v2406] = 0;	// L3782
  }
  int32_t txp_v2[4];	// L3783
  for (int v2408 = 0; v2408 < 4; v2408++) {	// L3784
    txp_v2[v2408] = 0;	// L3784
  }
  half txp_d2[4];	// L3785
  for (int v2410 = 0; v2410 < 4; v2410++) {	// L3786
    txp_d2[v2410] = (double)0.000000;	// L3786
  }
  int32_t txp_r2[4];	// L3787
  for (int v2412 = 0; v2412 < 4; v2412++) {	// L3788
    txp_r2[v2412] = 0;	// L3788
  }
  int32_t sc_r2[4];	// L3789
  for (int v2414 = 0; v2414 < 4; v2414++) {	// L3790
    sc_r2[v2414] = 2;	// L3790
  }
  int32_t cfg_isz2;	// L3791
  cfg_isz2 = 0;	// L3792
  int32_t cfg_itsz2;	// L3793
  cfg_itsz2 = 0;	// L3794
  uint8_t fetch_en2;	// L3795
  fetch_en2 = 0;	// L3796
  uint8_t instr_cnt2;	// L3797
  instr_cnt2 = 0;	// L3798
  uint8_t iter_cnt2;	// L3799
  iter_cnt2 = 0;	// L3800
  uint8_t condition_reg2;	// L3801
  condition_reg2 = 0;	// L3802
  uint8_t sb_v2[5];	// L3803
  for (int v2422 = 0; v2422 < 5; v2422++) {	// L3804
    sb_v2[v2422] = 0;	// L3804
  }
  uint8_t sb_dst2[5];	// L3805
  for (int v2424 = 0; v2424 < 5; v2424++) {	// L3806
    sb_dst2[v2424] = 0;	// L3806
  }
  uint8_t sb_cmp2[5];	// L3807
  for (int v2426 = 0; v2426 < 5; v2426++) {	// L3808
    sb_cmp2[v2426] = 0;	// L3808
  }
  uint8_t sb_rtr2[5];	// L3809
  for (int v2428 = 0; v2428 < 5; v2428++) {	// L3810
    sb_rtr2[v2428] = 0;	// L3810
  }
  uint8_t sb_inj2[5];	// L3811
  for (int v2430 = 0; v2430 < 5; v2430++) {	// L3812
    sb_inj2[v2430] = 0;	// L3812
  }
  uint8_t sb_dir2[5];	// L3813
  for (int v2432 = 0; v2432 < 5; v2432++) {	// L3814
    sb_dir2[v2432] = 0;	// L3814
  }
  uint8_t sb_id2[5];	// L3815
  for (int v2434 = 0; v2434 < 5; v2434++) {	// L3816
    sb_id2[v2434] = 0;	// L3816
  }
  uint8_t sb_rvld2[5];	// L3817
  for (int v2436 = 0; v2436 < 5; v2436++) {	// L3818
    sb_rvld2[v2436] = 0;	// L3818
  }
  uint8_t sb_ix2[5];	// L3819
  for (int v2438 = 0; v2438 < 5; v2438++) {	// L3820
    sb_ix2[v2438] = 0;	// L3820
  }
  uint8_t sb_long2[5];	// L3821
  for (int v2440 = 0; v2440 < 5; v2440++) {	// L3822
    sb_long2[v2440] = 0;	// L3822
  }
  half resq2[8];	// L3823
  for (int v2442 = 0; v2442 < 8; v2442++) {	// L3824
    resq2[v2442] = (double)0.000000;	// L3824
  }
  uint8_t cmpq2[8];	// L3825
  for (int v2444 = 0; v2444 < 8; v2444++) {	// L3826
    cmpq2[v2444] = 0;	// L3826
  }
  uint8_t resq_wr2;	// L3827
  resq_wr2 = 0;	// L3828
  ac_int<26, false> zpkt2;	// L3829
  zpkt2 = 0;	// L3830
  ac_int<17, false> zsys2;	// L3831
  zsys2 = 0;	// L3832
  int32_t zcr2;	// L3833
  zcr2 = 0;	// L3834
  ac_int<26, true> v2449 = zpkt2;	// L3835
  v2332.write(v2449);	// L3836
  ac_int<26, true> v2450 = zpkt2;	// L3837
  v2333.write(v2450);	// L3838
  ac_int<26, true> v2451 = zpkt2;	// L3839
  v2334.write(v2451);	// L3840
  ac_int<26, true> v2452 = zpkt2;	// L3841
  v2335.write(v2452);	// L3842
  ac_int<17, true> v2453 = zsys2;	// L3843
  v2336.write(v2453);	// L3844
  ac_int<17, true> v2454 = zsys2;	// L3845
  v2337.write(v2454);	// L3846
  ac_int<17, true> v2455 = zsys2;	// L3847
  v2338.write(v2455);	// L3848
  ac_int<17, true> v2456 = zsys2;	// L3849
  v2339.write(v2456);	// L3850
  int32_t v2457 = zcr2;	// L3851
  v2340.write(v2457);	// L3852
  int32_t v2458 = zcr2;	// L3853
  v2341.write(v2458);	// L3854
  int32_t v2459 = zcr2;	// L3855
  v2342.write(v2459);	// L3856
  int32_t v2460 = zcr2;	// L3857
  v2343.write(v2460);	// L3858
  int32_t v2461 = zcr2;	// L3859
  v2344.write(v2461);	// L3860
  int32_t v2462 = zcr2;	// L3861
  v2345.write(v2462);	// L3862
  int32_t v2463 = zcr2;	// L3863
  v2346.write(v2463);	// L3864
  int32_t v2464 = zcr2;	// L3865
  v2347.write(v2464);	// L3866
  ac_int<26, true> v2465 = zpkt2;	// L3867
  v2332.write(v2465);	// L3868
  ac_int<26, true> v2466 = zpkt2;	// L3869
  v2333.write(v2466);	// L3870
  ac_int<26, true> v2467 = zpkt2;	// L3871
  v2334.write(v2467);	// L3872
  ac_int<26, true> v2468 = zpkt2;	// L3873
  v2335.write(v2468);	// L3874
  ac_int<17, true> v2469 = zsys2;	// L3875
  v2336.write(v2469);	// L3876
  ac_int<17, true> v2470 = zsys2;	// L3877
  v2337.write(v2470);	// L3878
  ac_int<17, true> v2471 = zsys2;	// L3879
  v2338.write(v2471);	// L3880
  ac_int<17, true> v2472 = zsys2;	// L3881
  v2339.write(v2472);	// L3882
  int32_t v2473 = zcr2;	// L3883
  v2340.write(v2473);	// L3884
  int32_t v2474 = zcr2;	// L3885
  v2341.write(v2474);	// L3886
  int32_t v2475 = zcr2;	// L3887
  v2342.write(v2475);	// L3888
  int32_t v2476 = zcr2;	// L3889
  v2343.write(v2476);	// L3890
  int32_t v2477 = zcr2;	// L3891
  v2344.write(v2477);	// L3892
  int32_t v2478 = zcr2;	// L3893
  v2345.write(v2478);	// L3894
  int32_t v2479 = zcr2;	// L3895
  v2346.write(v2479);	// L3896
  int32_t v2480 = zcr2;	// L3897
  v2347.write(v2480);	// L3898
  ac_int<26, true> v2481 = zpkt2;	// L3899
  v2332.write(v2481);	// L3900
  ac_int<26, true> v2482 = zpkt2;	// L3901
  v2333.write(v2482);	// L3902
  ac_int<26, true> v2483 = zpkt2;	// L3903
  v2334.write(v2483);	// L3904
  ac_int<26, true> v2484 = zpkt2;	// L3905
  v2335.write(v2484);	// L3906
  ac_int<17, true> v2485 = zsys2;	// L3907
  v2336.write(v2485);	// L3908
  ac_int<17, true> v2486 = zsys2;	// L3909
  v2337.write(v2486);	// L3910
  ac_int<17, true> v2487 = zsys2;	// L3911
  v2338.write(v2487);	// L3912
  ac_int<17, true> v2488 = zsys2;	// L3913
  v2339.write(v2488);	// L3914
  int32_t v2489 = zcr2;	// L3915
  v2340.write(v2489);	// L3916
  int32_t v2490 = zcr2;	// L3917
  v2341.write(v2490);	// L3918
  int32_t v2491 = zcr2;	// L3919
  v2342.write(v2491);	// L3920
  int32_t v2492 = zcr2;	// L3921
  v2343.write(v2492);	// L3922
  int32_t v2493 = zcr2;	// L3923
  v2344.write(v2493);	// L3924
  int32_t v2494 = zcr2;	// L3925
  v2345.write(v2494);	// L3926
  int32_t v2495 = zcr2;	// L3927
  v2346.write(v2495);	// L3928
  int32_t v2496 = zcr2;	// L3929
  v2347.write(v2496);	// L3930
  ac_int<26, true> v2497 = zpkt2;	// L3931
  v2332.write(v2497);	// L3932
  ac_int<26, true> v2498 = zpkt2;	// L3933
  v2333.write(v2498);	// L3934
  ac_int<26, true> v2499 = zpkt2;	// L3935
  v2334.write(v2499);	// L3936
  ac_int<26, true> v2500 = zpkt2;	// L3937
  v2335.write(v2500);	// L3938
  ac_int<17, true> v2501 = zsys2;	// L3939
  v2336.write(v2501);	// L3940
  ac_int<17, true> v2502 = zsys2;	// L3941
  v2337.write(v2502);	// L3942
  ac_int<17, true> v2503 = zsys2;	// L3943
  v2338.write(v2503);	// L3944
  ac_int<17, true> v2504 = zsys2;	// L3945
  v2339.write(v2504);	// L3946
  int32_t v2505 = zcr2;	// L3947
  v2340.write(v2505);	// L3948
  int32_t v2506 = zcr2;	// L3949
  v2341.write(v2506);	// L3950
  int32_t v2507 = zcr2;	// L3951
  v2342.write(v2507);	// L3952
  int32_t v2508 = zcr2;	// L3953
  v2343.write(v2508);	// L3954
  int32_t v2509 = zcr2;	// L3955
  v2344.write(v2509);	// L3956
  int32_t v2510 = zcr2;	// L3957
  v2345.write(v2510);	// L3958
  int32_t v2511 = zcr2;	// L3959
  v2346.write(v2511);	// L3960
  int32_t v2512 = zcr2;	// L3961
  v2347.write(v2512);	// L3962
  ac_int<26, true> v2513 = zpkt2;	// L3963
  v2332.write(v2513);	// L3964
  ac_int<26, true> v2514 = zpkt2;	// L3965
  v2333.write(v2514);	// L3966
  ac_int<26, true> v2515 = zpkt2;	// L3967
  v2334.write(v2515);	// L3968
  ac_int<26, true> v2516 = zpkt2;	// L3969
  v2335.write(v2516);	// L3970
  ac_int<17, true> v2517 = zsys2;	// L3971
  v2336.write(v2517);	// L3972
  ac_int<17, true> v2518 = zsys2;	// L3973
  v2337.write(v2518);	// L3974
  ac_int<17, true> v2519 = zsys2;	// L3975
  v2338.write(v2519);	// L3976
  ac_int<17, true> v2520 = zsys2;	// L3977
  v2339.write(v2520);	// L3978
  int32_t v2521 = zcr2;	// L3979
  v2340.write(v2521);	// L3980
  int32_t v2522 = zcr2;	// L3981
  v2341.write(v2522);	// L3982
  int32_t v2523 = zcr2;	// L3983
  v2342.write(v2523);	// L3984
  int32_t v2524 = zcr2;	// L3985
  v2343.write(v2524);	// L3986
  int32_t v2525 = zcr2;	// L3987
  v2344.write(v2525);	// L3988
  int32_t v2526 = zcr2;	// L3989
  v2345.write(v2526);	// L3990
  int32_t v2527 = zcr2;	// L3991
  v2346.write(v2527);	// L3992
  int32_t v2528 = zcr2;	// L3993
  v2347.write(v2528);	// L3994
  ac_int<26, true> v2529 = oe_r2;	// L3995
  v2332.write(v2529);	// L3996
  ac_int<26, true> v2530 = ow_r2;	// L3997
  v2333.write(v2530);	// L3998
  ac_int<26, true> v2531 = os_r2;	// L3999
  v2334.write(v2531);	// L4000
  ac_int<26, true> v2532 = on_r2;	// L4001
  v2335.write(v2532);	// L4002
  ac_int<17, true> v2533 = txe_r2;	// L4003
  v2336.write(v2533);	// L4004
  ac_int<17, true> v2534 = txw_r2;	// L4005
  v2337.write(v2534);	// L4006
  ac_int<17, true> v2535 = txs_r2;	// L4007
  v2338.write(v2535);	// L4008
  ac_int<17, true> v2536 = txn_r2;	// L4009
  v2339.write(v2536);	// L4010
  int8_t v2537 = cre_r2;	// L4011
  v2340.write(v2537);	// L4012
  int8_t v2538 = crw_r2;	// L4013
  v2341.write(v2538);	// L4014
  int8_t v2539 = crs_r2;	// L4015
  v2342.write(v2539);	// L4016
  int8_t v2540 = crn_r2;	// L4017
  v2343.write(v2540);	// L4018
  int32_t v2541 = sc_r2[0];	// L4019
  v2346.write(v2541);	// L4020
  int32_t v2542 = sc_r2[1];	// L4021
  v2347.write(v2542);	// L4022
  int32_t v2543 = sc_r2[2];	// L4023
  v2344.write(v2543);	// L4024
  int32_t v2544 = sc_r2[3];	// L4025
  v2345.write(v2544);	// L4026
  l_S_t_0_t2: for (int t2 = 0; t2 < 10; t2++) {	// L4027
    ac_int<26, false> v2546 = v2348.read();	// L4028
    ac_int<26, false> p_w2;	// L4029
    p_w2 = v2546;	// L4030
    ac_int<26, false> v2548 = v2349.read();	// L4031
    ac_int<26, false> p_e2;	// L4032
    p_e2 = v2548;	// L4033
    ac_int<26, false> v2550 = v2350.read();	// L4034
    ac_int<26, false> p_n2;	// L4035
    p_n2 = v2550;	// L4036
    ac_int<26, false> v2552 = v2351.read();	// L4037
    ac_int<26, false> p_s2;	// L4038
    p_s2 = v2552;	// L4039
    int32_t v2554 = v2352.read();	// L4040
    uint8_t v2555 = rcred2[0];	// L4041
    ac_int<33, true> v2556 = v2555;	// L4042
    ac_int<33, true> v2557 = v2554;	// L4043
    ac_int<33, true> v2558 = v2556 + v2557;	// L4044
    uint8_t v2559 = v2558;	// L4045
    rcred2[0] = v2559;	// L4046
    int32_t v2560 = v2353.read();	// L4047
    uint8_t v2561 = rcred2[1];	// L4048
    ac_int<33, true> v2562 = v2561;	// L4049
    ac_int<33, true> v2563 = v2560;	// L4050
    ac_int<33, true> v2564 = v2562 + v2563;	// L4051
    uint8_t v2565 = v2564;	// L4052
    rcred2[1] = v2565;	// L4053
    int32_t v2566 = v2354.read();	// L4054
    uint8_t v2567 = rcred2[2];	// L4055
    ac_int<33, true> v2568 = v2567;	// L4056
    ac_int<33, true> v2569 = v2566;	// L4057
    ac_int<33, true> v2570 = v2568 + v2569;	// L4058
    uint8_t v2571 = v2570;	// L4059
    rcred2[2] = v2571;	// L4060
    int32_t v2572 = v2355.read();	// L4061
    uint8_t v2573 = rcred2[3];	// L4062
    ac_int<33, true> v2574 = v2573;	// L4063
    ac_int<33, true> v2575 = v2572;	// L4064
    ac_int<33, true> v2576 = v2574 + v2575;	// L4065
    uint8_t v2577 = v2576;	// L4066
    rcred2[3] = v2577;	// L4067
    int32_t v2578 = v2356.read();	// L4068
    int32_t v2579 = scred2[0];	// L4069
    ac_int<33, true> v2580 = v2579;	// L4070
    ac_int<33, true> v2581 = v2578;	// L4071
    ac_int<33, true> v2582 = v2580 + v2581;	// L4072
    int32_t v2583 = v2582;	// L4073
    scred2[0] = v2583;	// L4074
    int32_t v2584 = v2357.read();	// L4075
    int32_t v2585 = scred2[1];	// L4076
    ac_int<33, true> v2586 = v2585;	// L4077
    ac_int<33, true> v2587 = v2584;	// L4078
    ac_int<33, true> v2588 = v2586 + v2587;	// L4079
    int32_t v2589 = v2588;	// L4080
    scred2[1] = v2589;	// L4081
    int32_t v2590 = v2358.read();	// L4082
    int32_t v2591 = scred2[2];	// L4083
    ac_int<33, true> v2592 = v2591;	// L4084
    ac_int<33, true> v2593 = v2590;	// L4085
    ac_int<33, true> v2594 = v2592 + v2593;	// L4086
    int32_t v2595 = v2594;	// L4087
    scred2[2] = v2595;	// L4088
    int32_t v2596 = v2359.read();	// L4089
    int32_t v2597 = scred2[3];	// L4090
    ac_int<33, true> v2598 = v2597;	// L4091
    ac_int<33, true> v2599 = v2596;	// L4092
    ac_int<33, true> v2600 = v2598 + v2599;	// L4093
    int32_t v2601 = v2600;	// L4094
    scred2[3] = v2601;	// L4095
    ac_int<26, false> fin2[4];	// L4096
    for (int v2603 = 0; v2603 < 4; v2603++) {	// L4097
      fin2[v2603] = 0;	// L4097
    }
    ac_int<26, true> v2604 = p_w2;	// L4098
    fin2[0] = v2604;	// L4099
    ac_int<26, true> v2605 = p_e2;	// L4100
    fin2[1] = v2605;	// L4101
    ac_int<26, true> v2606 = p_n2;	// L4102
    fin2[2] = v2606;	// L4103
    ac_int<26, true> v2607 = p_s2;	// L4104
    fin2[3] = v2607;	// L4105
    l_S_d_0_d10: for (int d10 = 0; d10 < 4; d10++) {	// L4106
      ac_int<26, false> v2609 = fin2[d10];	// L4107
      bool v2610;
      ap_int<26> v2610_tmp = v2609;
      v2610 = v2610_tmp[25];	// L4108
      int32_t v2611 = v2610;	// L4109
      bool v2612 = v2611 == 1;	// L4110
      uint8_t v2613 = rbcnt2[d10];	// L4111
      int32_t v2614 = v2613;	// L4112
      bool v2615 = v2614 < 2;	// L4113
      bool v2616 = v2612 & v2615;	// L4114
      if (v2616) {	// L4115
        ac_int<26, false> v2617 = fin2[d10];	// L4116
        uint8_t v2618 = rbcnt2[d10];	// L4117
        int v2619 = v2618;	// L4118
        rbuf2[d10][v2619] = v2617;	// L4119
        uint8_t v2620 = rbcnt2[d10];	// L4120
        ac_int<33, true> v2621 = v2620;	// L4121
        ac_int<33, true> v2622 = v2621 + 1;	// L4122
        uint8_t v2623 = v2622;	// L4123
        rbcnt2[d10] = v2623;	// L4124
      }
    }
    ac_int<26, false> hd2[4];	// L4127
    for (int v2625 = 0; v2625 < 4; v2625++) {	// L4128
      hd2[v2625] = 0;	// L4128
    }
    int32_t hvld2[4];	// L4129
    for (int v2627 = 0; v2627 < 4; v2627++) {	// L4130
      hvld2[v2627] = 0;	// L4130
    }
    int32_t hit2[4];	// L4131
    for (int v2629 = 0; v2629 < 4; v2629++) {	// L4132
      hit2[v2629] = 0;	// L4132
    }
    int32_t axis2[4];	// L4133
    for (int v2631 = 0; v2631 < 4; v2631++) {	// L4134
      axis2[v2631] = 0;	// L4134
    }
    int32_t v2632 = col_id2;	// L4135
    axis2[0] = v2632;	// L4136
    int32_t v2633 = col_id2;	// L4137
    axis2[1] = v2633;	// L4138
    int32_t v2634 = row_id2;	// L4139
    axis2[2] = v2634;	// L4140
    int32_t v2635 = row_id2;	// L4141
    axis2[3] = v2635;	// L4142
    l_S_d_1_d11: for (int d11 = 0; d11 < 4; d11++) {	// L4143
      uint8_t v2637 = rbcnt2[d11];	// L4144
      int32_t v2638 = v2637;	// L4145
      bool v2639 = v2638 > 0;	// L4146
      if (v2639) {	// L4147
        ac_int<26, false> v2640 = rbuf2[d11][0];	// L4148
        hd2[d11] = v2640;	// L4149
        hvld2[d11] = 1;	// L4150
        ac_int<26, false> v2641 = hd2[d11];	// L4151
        ac_int<4, true> v2642;
        ap_int<26> v2642_tmp = v2641;
        v2642 = v2642_tmp(24, 21);	// L4152
        int32_t v2643 = axis2[d11];	// L4153
        int32_t v2644 = v2642;	// L4154
        bool v2645 = v2644 == v2643;	// L4155
        if (v2645) {	// L4156
          hit2[d11] = 1;	// L4157
        }
      }
    }
    ac_int<26, false> o_crv2;	// L4161
    o_crv2 = 0;	// L4162
    int32_t crv_in2;	// L4163
    crv_in2 = -1;	// L4164
    int32_t v2648 = hit2[3];	// L4165
    bool v2649 = v2648 == 1;	// L4166
    if (v2649) {	// L4167
      ac_int<26, false> v2650 = hd2[3];	// L4168
      o_crv2 = v2650;	// L4169
      crv_in2 = 3;	// L4170
    } else {
      int32_t v2651 = hit2[2];	// L4172
      bool v2652 = v2651 == 1;	// L4173
      if (v2652) {	// L4174
        ac_int<26, false> v2653 = hd2[2];	// L4175
        o_crv2 = v2653;	// L4176
        crv_in2 = 2;	// L4177
      } else {
        int32_t v2654 = hit2[1];	// L4179
        bool v2655 = v2654 == 1;	// L4180
        if (v2655) {	// L4181
          ac_int<26, false> v2656 = hd2[1];	// L4182
          o_crv2 = v2656;	// L4183
          crv_in2 = 1;	// L4184
        } else {
          int32_t v2657 = hit2[0];	// L4186
          bool v2658 = v2657 == 1;	// L4187
          if (v2658) {	// L4188
            ac_int<26, false> v2659 = hd2[0];	// L4189
            o_crv2 = v2659;	// L4190
            crv_in2 = 0;	// L4191
          }
        }
      }
    }
    ac_int<26, false> o_out2[4];	// L4196
    for (int v2661 = 0; v2661 < 4; v2661++) {	// L4197
      o_out2[v2661] = 0;	// L4197
    }
    int32_t pop2[4];	// L4198
    for (int v2663 = 0; v2663 < 4; v2663++) {	// L4199
      pop2[v2663] = 0;	// L4199
    }
    int32_t inj_done2;	// L4200
    inj_done2 = 0;	// L4201
    int32_t idir2;	// L4202
    idir2 = -1;	// L4203
    ac_int<26, true> v2666 = csd_pkt2;	// L4204
    bool v2667;
    ap_int<26> v2667_tmp = v2666;
    v2667 = v2667_tmp[25];	// L4205
    int32_t v2668 = v2667;	// L4206
    bool v2669 = v2668 == 1;	// L4207
    if (v2669) {	// L4208
      int32_t v2670 = csd_dir2;	// L4209
      ac_int<33, true> v2671 = v2670;	// L4210
      ac_int<33, true> v2672 = 3 - v2671;	// L4211
      int32_t v2673 = v2672;	// L4212
      idir2 = v2673;	// L4213
    }
    l_S_o_2_o2: for (int o2 = 0; o2 < 4; o2++) {	// L4215
      uint8_t v2675 = rcred2[o2];	// L4216
      int32_t v2676 = v2675;	// L4217
      bool v2677 = v2676 > 0;	// L4218
      if (v2677) {	// L4219
        int32_t v2678 = idir2;	// L4220
        ac_int<33, true> v2679 = v2678;	// L4221
        ac_int<33, true> v2680 = o2;	// L4222
        bool v2681 = v2679 == v2680;	// L4223
        if (v2681) {	// L4224
          ac_int<26, true> v2682 = csd_pkt2;	// L4225
          o_out2[o2] = v2682;	// L4226
          uint8_t v2683 = rcred2[o2];	// L4227
          ac_int<33, true> v2684 = v2683;	// L4228
          ac_int<33, true> v2685 = v2684 - 1;	// L4229
          uint8_t v2686 = v2685;	// L4230
          rcred2[o2] = v2686;	// L4231
          inj_done2 = 1;	// L4232
        } else {
          int32_t v2687 = hvld2[o2];	// L4234
          bool v2688 = v2687 == 1;	// L4235
          int32_t v2689 = hit2[o2];	// L4236
          bool v2690 = v2689 == 0;	// L4237
          bool v2691 = v2688 & v2690;	// L4238
          if (v2691) {	// L4239
            ac_int<26, false> v2692 = hd2[o2];	// L4240
            o_out2[o2] = v2692;	// L4241
            uint8_t v2693 = rcred2[o2];	// L4242
            ac_int<33, true> v2694 = v2693;	// L4243
            ac_int<33, true> v2695 = v2694 - 1;	// L4244
            uint8_t v2696 = v2695;	// L4245
            rcred2[o2] = v2696;	// L4246
            pop2[o2] = 1;	// L4247
          }
        }
      }
    }
    int32_t v2697 = crv_in2;	// L4252
    bool v2698 = v2697 >= 0;	// L4253
    if (v2698) {	// L4254
      int32_t v2699 = crv_in2;	// L4255
      int v2700 = v2699;	// L4256
      pop2[v2700] = 1;	// L4257
    }
    int32_t ret2[4];	// L4259
    for (int v2702 = 0; v2702 < 4; v2702++) {	// L4260
      ret2[v2702] = 0;	// L4260
    }
    l_S_d_3_d12: for (int d12 = 0; d12 < 4; d12++) {	// L4261
      int32_t v2704 = pop2[d12];	// L4262
      bool v2705 = v2704 == 1;	// L4263
      if (v2705) {	// L4264
        l_S_sft_3_sft2: for (int sft2 = 0; sft2 < 1; sft2++) {	// L4265
          ac_int<26, false> v2707 = rbuf2[d12][(sft2 + 1)];	// L4266
          rbuf2[d12][sft2] = v2707;	// L4267
        }
        uint8_t v2708 = rbcnt2[d12];	// L4269
        ac_int<33, true> v2709 = v2708;	// L4270
        ac_int<33, true> v2710 = v2709 - 1;	// L4271
        uint8_t v2711 = v2710;	// L4272
        rbcnt2[d12] = v2711;	// L4273
        ret2[d12] = 1;	// L4274
      }
    }
    int32_t v2712 = ret2[0];	// L4277
    uint8_t v2713 = v2712;	// L4278
    cre_r2 = v2713;	// L4279
    int32_t v2714 = ret2[1];	// L4280
    uint8_t v2715 = v2714;	// L4281
    crw_r2 = v2715;	// L4282
    int32_t v2716 = ret2[2];	// L4283
    uint8_t v2717 = v2716;	// L4284
    crs_r2 = v2717;	// L4285
    int32_t v2718 = ret2[3];	// L4286
    uint8_t v2719 = v2718;	// L4287
    crn_r2 = v2719;	// L4288
    ac_int<26, false> v2720 = o_out2[0];	// L4289
    oe_r2 = v2720;	// L4290
    ac_int<26, false> v2721 = o_out2[1];	// L4291
    ow_r2 = v2721;	// L4292
    ac_int<26, false> v2722 = o_out2[2];	// L4293
    os_r2 = v2722;	// L4294
    ac_int<26, false> v2723 = o_out2[3];	// L4295
    on_r2 = v2723;	// L4296
    int32_t v2724 = inj_done2;	// L4297
    bool v2725 = v2724 == 1;	// L4298
    if (v2725) {	// L4299
      csd_pkt2 = 0;	// L4300
    }
    ac_int<26, true> v2726 = o_crv2;	// L4302
    bool v2727;
    ap_int<26> v2727_tmp = v2726;
    v2727 = v2727_tmp[25];	// L4303
    int32_t v2728 = v2727;	// L4304
    crv_vld2 = v2728;	// L4305
    ac_int<26, true> v2729 = o_crv2;	// L4306
    int16_t v2730;
    ap_int<26> v2730_tmp = v2729;
    v2730 = v2730_tmp(15, 0);	// L4307
    half v2731;
    union { uint16_t from; half to;} _converter_v2730_to_v2731 = {};
    _converter_v2730_to_v2731.from = v2730;
    v2731 = _converter_v2730_to_v2731.to;	// L4308
    crv_data2 = v2731;	// L4309
    ac_int<26, true> v2732 = o_crv2;	// L4310
    ac_int<4, true> v2733;
    ap_int<26> v2733_tmp = v2732;
    v2733 = v2733_tmp(19, 16);	// L4311
    int32_t v2734 = v2733;	// L4312
    crv_addr2 = v2734;	// L4313
    ac_int<26, true> v2735 = o_crv2;	// L4314
    bool v2736;
    ap_int<26> v2736_tmp = v2735;
    v2736 = v2736_tmp[20];	// L4315
    int32_t v2737 = v2736;	// L4316
    crv_mode2 = v2737;	// L4317
    ac_int<26, true> v2738 = o_crv2;	// L4318
    int16_t v2739;
    ap_int<26> v2739_tmp = v2738;
    v2739 = v2739_tmp(15, 0);	// L4319
    int32_t v2740 = v2739;	// L4320
    crv_raw2 = v2740;	// L4321
    ac_int<17, false> v2741 = v2360.read();	// L4322
    ac_int<17, false> rx_w2;	// L4323
    rx_w2 = v2741;	// L4324
    ac_int<17, false> v2743 = v2361.read();	// L4325
    ac_int<17, false> rx_e2;	// L4326
    rx_e2 = v2743;	// L4327
    ac_int<17, false> v2745 = v2362.read();	// L4328
    ac_int<17, false> rx_n2;	// L4329
    rx_n2 = v2745;	// L4330
    ac_int<17, false> v2747 = v2363.read();	// L4331
    ac_int<17, false> rx_s2;	// L4332
    rx_s2 = v2747;	// L4333
    half rxv2[4];	// L4334
    for (int v2750 = 0; v2750 < 4; v2750++) {	// L4335
      rxv2[v2750] = (double)0.000000;	// L4335
    }
    int32_t rxvld2[4];	// L4336
    for (int v2752 = 0; v2752 < 4; v2752++) {	// L4337
      rxvld2[v2752] = 0;	// L4337
    }
    ac_int<17, true> v2753 = rx_n2;	// L4338
    int16_t v2754;
    ap_int<17> v2754_tmp = v2753;
    v2754 = v2754_tmp(16, 1);	// L4339
    half v2755;
    union { uint16_t from; half to;} _converter_v2754_to_v2755 = {};
    _converter_v2754_to_v2755.from = v2754;
    v2755 = _converter_v2754_to_v2755.to;	// L4340
    rxv2[0] = v2755;	// L4341
    ac_int<17, true> v2756 = rx_n2;	// L4342
    bool v2757;
    ap_int<17> v2757_tmp = v2756;
    v2757 = v2757_tmp[0];	// L4343
    int32_t v2758 = v2757;	// L4344
    rxvld2[0] = v2758;	// L4345
    ac_int<17, true> v2759 = rx_s2;	// L4346
    int16_t v2760;
    ap_int<17> v2760_tmp = v2759;
    v2760 = v2760_tmp(16, 1);	// L4347
    half v2761;
    union { uint16_t from; half to;} _converter_v2760_to_v2761 = {};
    _converter_v2760_to_v2761.from = v2760;
    v2761 = _converter_v2760_to_v2761.to;	// L4348
    rxv2[1] = v2761;	// L4349
    ac_int<17, true> v2762 = rx_s2;	// L4350
    bool v2763;
    ap_int<17> v2763_tmp = v2762;
    v2763 = v2763_tmp[0];	// L4351
    int32_t v2764 = v2763;	// L4352
    rxvld2[1] = v2764;	// L4353
    ac_int<17, true> v2765 = rx_w2;	// L4354
    int16_t v2766;
    ap_int<17> v2766_tmp = v2765;
    v2766 = v2766_tmp(16, 1);	// L4355
    half v2767;
    union { uint16_t from; half to;} _converter_v2766_to_v2767 = {};
    _converter_v2766_to_v2767.from = v2766;
    v2767 = _converter_v2766_to_v2767.to;	// L4356
    rxv2[2] = v2767;	// L4357
    ac_int<17, true> v2768 = rx_w2;	// L4358
    bool v2769;
    ap_int<17> v2769_tmp = v2768;
    v2769 = v2769_tmp[0];	// L4359
    int32_t v2770 = v2769;	// L4360
    rxvld2[2] = v2770;	// L4361
    ac_int<17, true> v2771 = rx_e2;	// L4362
    int16_t v2772;
    ap_int<17> v2772_tmp = v2771;
    v2772 = v2772_tmp(16, 1);	// L4363
    half v2773;
    union { uint16_t from; half to;} _converter_v2772_to_v2773 = {};
    _converter_v2772_to_v2773.from = v2772;
    v2773 = _converter_v2772_to_v2773.to;	// L4364
    rxv2[3] = v2773;	// L4365
    ac_int<17, true> v2774 = rx_e2;	// L4366
    bool v2775;
    ap_int<17> v2775_tmp = v2774;
    v2775 = v2775_tmp[0];	// L4367
    int32_t v2776 = v2775;	// L4368
    rxvld2[3] = v2776;	// L4369
    l_S_d_5_d13: for (int d13 = 0; d13 < 4; d13++) {	// L4370
      int32_t v2778 = rxvld2[d13];	// L4371
      bool v2779 = v2778 == 1;	// L4372
      uint8_t v2780 = hold_cnt2[d13];	// L4373
      int32_t v2781 = v2780;	// L4374
      bool v2782 = v2781 < 2;	// L4375
      bool v2783 = v2779 & v2782;	// L4376
      if (v2783) {	// L4377
        half v2784 = rxv2[d13];	// L4378
        uint8_t v2785 = hold_cnt2[d13];	// L4379
        int v2786 = v2785;	// L4380
        hold_v2[d13][v2786] = v2784;	// L4381
        uint8_t v2787 = hold_cnt2[d13];	// L4382
        ac_int<33, true> v2788 = v2787;	// L4383
        ac_int<33, true> v2789 = v2788 + 1;	// L4384
        uint8_t v2790 = v2789;	// L4385
        hold_cnt2[d13] = v2790;	// L4386
      }
    }
    int32_t retire_ok2;	// L4389
    retire_ok2 = 1;	// L4390
    uint8_t v2792 = sb_v2[0];	// L4391
    int32_t v2793 = v2792;	// L4392
    bool v2794 = v2793 == 1;	// L4393
    uint8_t v2795 = sb_rtr2[0];	// L4394
    int32_t v2796 = v2795;	// L4395
    bool v2797 = v2796 == 0;	// L4396
    uint8_t v2798 = sb_dst2[0];	// L4397
    int32_t v2799 = v2798;	// L4398
    bool v2800 = v2799 >= 12;	// L4399
    bool v2801 = v2794 & v2797;	// L4400
    bool v2802 = v2801 & v2800;	// L4401
    if (v2802) {	// L4402
      uint8_t v2803 = sb_rvld2[0];	// L4403
      int32_t v2804 = v2803;	// L4404
      bool v2805 = v2804 == 1;	// L4405
      uint8_t v2806 = sb_dst2[0];	// L4406
      int32_t v2807 = v2806;	// L4407
      int32_t v2808 = v2807 & 3;	// L4408
      int v2809 = v2808;	// L4409
      int32_t v2810 = txp_v2[v2809];	// L4410
      bool v2811 = v2810 == 1;	// L4411
      bool v2812 = v2805 & v2811;	// L4412
      if (v2812) {	// L4413
        retire_ok2 = 0;	// L4414
      }
    }
    uint8_t v2813 = sb_v2[0];	// L4417
    int32_t v2814 = v2813;	// L4418
    bool v2815 = v2814 == 1;	// L4419
    int32_t v2816 = retire_ok2;	// L4420
    bool v2817 = v2816 == 1;	// L4421
    bool v2818 = v2815 & v2817;	// L4422
    if (v2818) {	// L4423
      uint8_t v2819 = sb_ix2[0];	// L4424
      int v2820 = v2819;	// L4425
      half v2821 = resq2[v2820];	// L4426
      half wb2;	// L4427
      wb2 = v2821;	// L4428
      uint8_t v2823 = sb_cmp2[0];	// L4429
      int32_t v2824 = v2823;	// L4430
      bool v2825 = v2824 == 1;	// L4431
      if (v2825) {	// L4432
        uint8_t v2826 = sb_ix2[0];	// L4433
        int v2827 = v2826;	// L4434
        uint8_t v2828 = cmpq2[v2827];	// L4435
        condition_reg2 = v2828;	// L4436
      }
      uint8_t v2829 = sb_rtr2[0];	// L4438
      int32_t v2830 = v2829;	// L4439
      bool v2831 = v2830 == 1;	// L4440
      if (v2831) {	// L4441
        uint8_t v2832 = sb_inj2[0];	// L4442
        int32_t v2833 = v2832;	// L4443
        bool v2834 = v2833 == 1;	// L4444
        ac_int<26, true> v2835 = csd_pkt2;	// L4445
        bool v2836;
        ap_int<26> v2836_tmp = v2835;
        v2836 = v2836_tmp[25];	// L4446
        int32_t v2837 = v2836;	// L4447
        bool v2838 = v2837 == 0;	// L4448
        bool v2839 = v2834 & v2838;	// L4449
        if (v2839) {	// L4450
          half v2840 = wb2;	// L4451
          uint16_t v2841;
          union { half from; uint16_t to;} _converter_v2840_to_v2841 = {};
          _converter_v2840_to_v2841.from = v2840;
          v2841 = _converter_v2840_to_v2841.to;	// L4452
          ac_int<26, true> v2842 = csd_pkt2;	// L4453
          ac_int<26, true> v2843;
          ap_int<26> v2843_tmp = v2842;
          v2843_tmp(15, 0) = v2841;
          v2843 = v2843_tmp;	// L4454
          csd_pkt2 = v2843;	// L4455
          uint8_t v2844 = sb_dst2[0];	// L4456
          ac_int<4, false> v2845 = v2844;	// L4457
          ac_int<26, true> v2846 = csd_pkt2;	// L4458
          ac_int<26, true> v2847;
          ap_int<26> v2847_tmp = v2846;
          v2847_tmp(19, 16) = v2845;
          v2847 = v2847_tmp;	// L4459
          csd_pkt2 = v2847;	// L4460
          uint8_t v2848 = sb_id2[0];	// L4461
          ac_int<4, false> v2849 = v2848;	// L4462
          ac_int<26, true> v2850 = csd_pkt2;	// L4463
          ac_int<26, true> v2851;
          ap_int<26> v2851_tmp = v2850;
          v2851_tmp(24, 21) = v2849;
          v2851 = v2851_tmp;	// L4464
          csd_pkt2 = v2851;	// L4465
          uint8_t v2852 = sb_rvld2[0];	// L4466
          bool v2853 = v2852;	// L4467
          ac_int<26, true> v2854 = csd_pkt2;	// L4468
          ac_int<26, true> v2855;
          ap_int<26> v2855_tmp = v2854;
          v2855_tmp[25] = v2853;          v2855 = v2855_tmp;	// L4469
          csd_pkt2 = v2855;	// L4470
          uint8_t v2856 = sb_dir2[0];	// L4471
          int32_t v2857 = v2856;	// L4472
          csd_dir2 = v2857;	// L4473
        }
      } else {
        uint8_t v2858 = sb_dst2[0];	// L4476
        int32_t v2859 = v2858;	// L4477
        bool v2860 = v2859 >= 12;	// L4478
        if (v2860) {	// L4479
          uint8_t v2861 = sb_rvld2[0];	// L4480
          int32_t v2862 = v2861;	// L4481
          bool v2863 = v2862 == 1;	// L4482
          if (v2863) {	// L4483
            uint8_t v2864 = sb_dst2[0];	// L4484
            int32_t v2865 = v2864;	// L4485
            int32_t v2866 = v2865 & 3;	// L4486
            int v2867 = v2866;	// L4487
            txp_v2[v2867] = 1;	// L4488
            half v2868 = wb2;	// L4489
            uint8_t v2869 = sb_dst2[0];	// L4490
            int32_t v2870 = v2869;	// L4491
            int32_t v2871 = v2870 & 3;	// L4492
            int v2872 = v2871;	// L4493
            txp_d2[v2872] = v2868;	// L4494
            uint8_t v2873 = sb_dst2[0];	// L4495
            int32_t v2874 = v2873;	// L4496
            int32_t v2875 = v2874 & 3;	// L4497
            int v2876 = v2875;	// L4498
            txp_r2[v2876] = 1;	// L4499
          }
        } else {
          uint8_t v2877 = sb_rvld2[0];	// L4502
          int32_t v2878 = v2877;	// L4503
          bool v2879 = v2878 == 1;	// L4504
          if (v2879) {	// L4505
            uint8_t v2880 = sb_dst2[0];	// L4506
            int32_t v2881 = v2880;	// L4507
            bool v2882 = v2881 < 8;	// L4508
            int32_t v2883 = dsmask2;	// L4509
            int32_t v2884 = v2883 >> v2881;	// L4512
            int32_t v2885 = v2884 & 1;	// L4513
            bool v2886 = v2885 == 1;	// L4514
            bool v2887 = v2882 & v2886;	// L4515
            if (v2887) {	// L4516
              uint8_t v2888 = sb_dst2[0];	// L4517
              int v2889 = v2888;	// L4518
              int32_t v2890 = drf_full2[v2889];	// L4519
              bool v2891 = v2890 == 0;	// L4520
              if (v2891) {	// L4521
                half v2892 = wb2;	// L4522
                uint8_t v2893 = sb_dst2[0];	// L4523
                int v2894 = v2893;	// L4524
                drf2[v2894] = v2892;	// L4525
                uint8_t v2895 = sb_dst2[0];	// L4526
                int v2896 = v2895;	// L4527
                drf_full2[v2896] = 1;	// L4528
              }
            } else {
              half v2897 = wb2;	// L4531
              uint8_t v2898 = sb_dst2[0];	// L4532
              int32_t v2899 = v2898;	// L4533
              int32_t v2900 = v2899 & 7;	// L4534
              int v2901 = v2900;	// L4535
              drf2[v2901] = v2897;	// L4536
            }
          }
        }
      }
    }
    int32_t pc2;	// L4542
    pc2 = -1;	// L4543
    int8_t v2903 = fetch_en2;	// L4544
    int32_t v2904 = v2903;	// L4545
    bool v2905 = v2904 == 1;	// L4546
    if (v2905) {	// L4547
      int8_t v2906 = instr_cnt2;	// L4548
      int32_t v2907 = v2906;	// L4549
      pc2 = v2907;	// L4550
    }
    int32_t instr2;	// L4552
    instr2 = 0;	// L4553
    int32_t v2909 = pc2;	// L4554
    bool v2910 = v2909 >= 0;	// L4555
    if (v2910) {	// L4556
      int32_t v2911 = pc2;	// L4557
      int v2912 = v2911;	// L4558
      int32_t v2913 = irf2[v2912];	// L4559
      instr2 = v2913;	// L4560
    }
    int32_t v2914 = instr2;	// L4562
    int32_t v2915 = v2914 & 15;	// L4563
    int32_t op2;	// L4564
    op2 = v2915;	// L4565
    int32_t v2917 = instr2;	// L4566
    int32_t v2918 = v2917 >> 4;	// L4567
    int32_t v2919 = v2918 & 15;	// L4568
    int32_t dst2;	// L4569
    dst2 = v2919;	// L4570
    int32_t v2921 = instr2;	// L4571
    int32_t v2922 = v2921 >> 8;	// L4572
    int32_t v2923 = v2922 & 15;	// L4573
    int32_t s12;	// L4574
    s12 = v2923;	// L4575
    int32_t v2925 = instr2;	// L4576
    int32_t v2926 = v2925 >> 12;	// L4577
    int32_t v2927 = v2926 & 15;	// L4578
    int32_t s22;	// L4579
    s22 = v2927;	// L4580
    half a2;	// L4581
    a2 = (double)0.000000;	// L4582
    half b2;	// L4583
    b2 = (double)0.000000;	// L4584
    int32_t v2931 = s12;	// L4585
    bool v2932 = v2931 >= 12;	// L4586
    if (v2932) {	// L4587
      int32_t v2933 = s12;	// L4588
      int32_t v2934 = v2933 & 3;	// L4589
      int v2935 = v2934;	// L4590
      half v2936 = hold_v2[v2935][0];	// L4591
      a2 = v2936;	// L4592
    } else {
      int32_t v2937 = s12;	// L4594
      int v2938 = v2937;	// L4595
      half v2939 = drf2[v2938];	// L4596
      a2 = v2939;	// L4597
    }
    int32_t v2940 = s22;	// L4599
    bool v2941 = v2940 >= 12;	// L4600
    if (v2941) {	// L4601
      int32_t v2942 = s22;	// L4602
      int32_t v2943 = v2942 & 3;	// L4603
      int v2944 = v2943;	// L4604
      half v2945 = hold_v2[v2944][0];	// L4605
      b2 = v2945;	// L4606
    } else {
      int32_t v2946 = s22;	// L4608
      int v2947 = v2946;	// L4609
      half v2948 = drf2[v2947];	// L4610
      b2 = v2948;	// L4611
    }
    int32_t a_vld2;	// L4613
    a_vld2 = 1;	// L4614
    int32_t b_vld2;	// L4615
    b_vld2 = 1;	// L4616
    int32_t v2951 = s12;	// L4617
    bool v2952 = v2951 >= 12;	// L4618
    if (v2952) {	// L4619
      a_vld2 = 0;	// L4620
      int32_t v2953 = s12;	// L4621
      int32_t v2954 = v2953 & 3;	// L4622
      int v2955 = v2954;	// L4623
      uint8_t v2956 = hold_cnt2[v2955];	// L4624
      int32_t v2957 = v2956;	// L4625
      bool v2958 = v2957 > 0;	// L4626
      if (v2958) {	// L4627
        a_vld2 = 1;	// L4628
      }
    }
    int32_t v2959 = s22;	// L4631
    bool v2960 = v2959 >= 12;	// L4632
    if (v2960) {	// L4633
      b_vld2 = 0;	// L4634
      int32_t v2961 = s22;	// L4635
      int32_t v2962 = v2961 & 3;	// L4636
      int v2963 = v2962;	// L4637
      uint8_t v2964 = hold_cnt2[v2963];	// L4638
      int32_t v2965 = v2964;	// L4639
      bool v2966 = v2965 > 0;	// L4640
      if (v2966) {	// L4641
        b_vld2 = 1;	// L4642
      }
    }
    int32_t v2967 = s12;	// L4645
    bool v2968 = v2967 < 8;	// L4646
    int32_t v2969 = dsmask2;	// L4647
    int32_t v2970 = v2969 >> v2967;	// L4649
    int32_t v2971 = v2970 & 1;	// L4650
    bool v2972 = v2971 == 1;	// L4651
    bool v2973 = v2968 & v2972;	// L4652
    if (v2973) {	// L4653
      int32_t v2974 = s12;	// L4654
      int v2975 = v2974;	// L4655
      int32_t v2976 = drf_full2[v2975];	// L4656
      bool v2977 = v2976 == 0;	// L4657
      if (v2977) {	// L4658
        a_vld2 = 0;	// L4659
      }
    }
    int32_t v2978 = s22;	// L4662
    bool v2979 = v2978 < 8;	// L4663
    int32_t v2980 = dsmask2;	// L4664
    int32_t v2981 = v2980 >> v2978;	// L4666
    int32_t v2982 = v2981 & 1;	// L4667
    bool v2983 = v2982 == 1;	// L4668
    bool v2984 = v2979 & v2983;	// L4669
    if (v2984) {	// L4670
      int32_t v2985 = s22;	// L4671
      int v2986 = v2985;	// L4672
      int32_t v2987 = drf_full2[v2986];	// L4673
      bool v2988 = v2987 == 0;	// L4674
      if (v2988) {	// L4675
        b_vld2 = 0;	// L4676
      }
    }
    int32_t binop2;	// L4679
    binop2 = 0;	// L4680
    int32_t v2990 = op2;	// L4681
    bool v2991 = v2990 == 0;	// L4682
    bool v2992 = v2990 == 1;	// L4684
    bool v2993 = v2990 == 2;	// L4686
    bool v2994 = v2990 == 8;	// L4688
    bool v2995 = v2990 == 9;	// L4690
    bool v2996 = v2991 | v2992;	// L4691
    bool v2997 = v2996 | v2993;	// L4692
    bool v2998 = v2997 | v2994;	// L4693
    bool v2999 = v2998 | v2995;	// L4694
    if (v2999) {	// L4695
      binop2 = 1;	// L4696
    }
    int32_t raw2;	// L4698
    raw2 = 0;	// L4699
    int32_t cmp_busy2;	// L4700
    cmp_busy2 = 0;	// L4701
    int32_t fwd_a2;	// L4702
    fwd_a2 = 0;	// L4703
    int32_t fwd_a_ix2;	// L4704
    fwd_a_ix2 = 0;	// L4705
    int32_t raw_a2;	// L4706
    raw_a2 = 0;	// L4707
    int32_t fwd_b2;	// L4708
    fwd_b2 = 0;	// L4709
    int32_t fwd_b_ix2;	// L4710
    fwd_b_ix2 = 0;	// L4711
    int32_t raw_b2;	// L4712
    raw_b2 = 0;	// L4713
    l_S_k_6_k4: for (int k4 = 0; k4 < 4; k4++) {	// L4714
      ac_int<34, true> v3009 = k4;	// L4715
      ac_int<34, true> v3010 = v3009 + 1;	// L4716
      int32_t v3011 = v3010;	// L4717
      int32_t kk2;	// L4718
      kk2 = v3011;	// L4719
      int32_t v3013 = kk2;	// L4720
      ac_int<34, true> v3014 = v3013;	// L4721
      ac_int<34, true> v3015 = 4 - v3014;	// L4722
      int32_t v3016 = v3015;	// L4723
      int32_t inflight2;	// L4724
      inflight2 = v3016;	// L4725
      int32_t need2;	// L4726
      need2 = 0;	// L4727
      int32_t v3019 = kk2;	// L4728
      int v3020 = v3019;	// L4729
      uint8_t v3021 = sb_long2[v3020];	// L4730
      int32_t v3022 = v3021;	// L4731
      bool v3023 = v3022 == 1;	// L4732
      if (v3023) {	// L4733
        need2 = 1;	// L4734
      }
      int32_t rdy2;	// L4736
      rdy2 = 0;	// L4737
      int32_t v3025 = inflight2;	// L4738
      int32_t v3026 = need2;	// L4739
      bool v3027 = v3025 >= v3026;	// L4740
      if (v3027) {	// L4741
        rdy2 = 1;	// L4742
      }
      int32_t v3028 = kk2;	// L4744
      int v3029 = v3028;	// L4745
      uint8_t v3030 = sb_v2[v3029];	// L4746
      int32_t v3031 = v3030;	// L4747
      bool v3032 = v3031 == 1;	// L4748
      uint8_t v3033 = sb_rtr2[v3029];	// L4751
      int32_t v3034 = v3033;	// L4752
      bool v3035 = v3034 == 0;	// L4753
      uint8_t v3036 = sb_dst2[v3029];	// L4756
      int32_t v3037 = v3036;	// L4757
      bool v3038 = v3037 < 12;	// L4758
      bool v3039 = v3032 & v3035;	// L4759
      bool v3040 = v3039 & v3038;	// L4760
      if (v3040) {	// L4761
        int32_t v3041 = s12;	// L4762
        bool v3042 = v3041 < 12;	// L4763
        int32_t v3043 = kk2;	// L4764
        int v3044 = v3043;	// L4765
        uint8_t v3045 = sb_dst2[v3044];	// L4766
        int32_t v3046 = v3045;	// L4767
        int32_t v3047 = v3046 & 7;	// L4768
        int32_t v3048 = v3041 & 7;	// L4770
        bool v3049 = v3047 == v3048;	// L4771
        bool v3050 = v3042 & v3049;	// L4772
        if (v3050) {	// L4773
          int32_t v3051 = rdy2;	// L4774
          bool v3052 = v3051 == 1;	// L4775
          if (v3052) {	// L4776
            fwd_a2 = 1;	// L4777
            int32_t v3053 = kk2;	// L4778
            int v3054 = v3053;	// L4779
            uint8_t v3055 = sb_ix2[v3054];	// L4780
            int32_t v3056 = v3055;	// L4781
            fwd_a_ix2 = v3056;	// L4782
            raw_a2 = 0;	// L4783
          } else {
            fwd_a2 = 0;	// L4785
            raw_a2 = 1;	// L4786
          }
        }
        int32_t v3057 = binop2;	// L4789
        bool v3058 = v3057 == 1;	// L4790
        int32_t v3059 = s22;	// L4791
        bool v3060 = v3059 < 12;	// L4792
        int32_t v3061 = kk2;	// L4793
        int v3062 = v3061;	// L4794
        uint8_t v3063 = sb_dst2[v3062];	// L4795
        int32_t v3064 = v3063;	// L4796
        int32_t v3065 = v3064 & 7;	// L4797
        int32_t v3066 = v3059 & 7;	// L4799
        bool v3067 = v3065 == v3066;	// L4800
        bool v3068 = v3058 & v3060;	// L4801
        bool v3069 = v3068 & v3067;	// L4802
        if (v3069) {	// L4803
          int32_t v3070 = rdy2;	// L4804
          bool v3071 = v3070 == 1;	// L4805
          if (v3071) {	// L4806
            fwd_b2 = 1;	// L4807
            int32_t v3072 = kk2;	// L4808
            int v3073 = v3072;	// L4809
            uint8_t v3074 = sb_ix2[v3073];	// L4810
            int32_t v3075 = v3074;	// L4811
            fwd_b_ix2 = v3075;	// L4812
            raw_b2 = 0;	// L4813
          } else {
            fwd_b2 = 0;	// L4815
            raw_b2 = 1;	// L4816
          }
        }
      }
      int32_t v3076 = kk2;	// L4820
      int v3077 = v3076;	// L4821
      uint8_t v3078 = sb_v2[v3077];	// L4822
      int32_t v3079 = v3078;	// L4823
      bool v3080 = v3079 == 1;	// L4824
      uint8_t v3081 = sb_cmp2[v3077];	// L4827
      int32_t v3082 = v3081;	// L4828
      bool v3083 = v3082 == 1;	// L4829
      bool v3084 = v3080 & v3083;	// L4830
      if (v3084) {	// L4831
        cmp_busy2 = 1;	// L4832
      }
    }
    int32_t v3085 = raw_a2;	// L4835
    raw2 = v3085;	// L4836
    int32_t v3086 = binop2;	// L4837
    bool v3087 = v3086 == 1;	// L4838
    int32_t v3088 = raw_b2;	// L4839
    bool v3089 = v3088 == 1;	// L4840
    bool v3090 = v3087 & v3089;	// L4841
    if (v3090) {	// L4842
      raw2 = 1;	// L4843
    }
    int32_t v3091 = fwd_a2;	// L4845
    bool v3092 = v3091 == 1;	// L4846
    if (v3092) {	// L4847
      int32_t v3093 = fwd_a_ix2;	// L4848
      int v3094 = v3093;	// L4849
      half v3095 = resq2[v3094];	// L4850
      a2 = v3095;	// L4851
      a_vld2 = 1;	// L4852
    }
    int32_t v3096 = fwd_b2;	// L4854
    bool v3097 = v3096 == 1;	// L4855
    if (v3097) {	// L4856
      int32_t v3098 = fwd_b_ix2;	// L4857
      int v3099 = v3098;	// L4858
      half v3100 = resq2[v3099];	// L4859
      b2 = v3100;	// L4860
      b_vld2 = 1;	// L4861
    }
    int32_t is_cond2;	// L4863
    is_cond2 = 0;	// L4864
    int32_t v3102 = op2;	// L4865
    bool v3103 = v3102 >= 12;	// L4866
    ac_int<33, true> v3104 = v3102;	// L4868
    bool v3105 = v3104 <= 15;	// L4869
    bool v3106 = v3103 & v3105;	// L4870
    if (v3106) {	// L4871
      is_cond2 = 1;	// L4872
    }
    int32_t grant2;	// L4874
    grant2 = 0;	// L4875
    int32_t v3108 = pc2;	// L4876
    bool v3109 = v3108 >= 0;	// L4877
    if (v3109) {	// L4878
      grant2 = 1;	// L4879
    }
    int32_t v3110 = pc2;	// L4881
    bool v3111 = v3110 >= 0;	// L4882
    int32_t v3112 = a_vld2;	// L4883
    bool v3113 = v3112 == 0;	// L4884
    int32_t v3114 = binop2;	// L4885
    bool v3115 = v3114 == 1;	// L4886
    int32_t v3116 = b_vld2;	// L4887
    bool v3117 = v3116 == 0;	// L4888
    bool v3118 = v3115 & v3117;	// L4889
    bool v3119 = v3113 | v3118;	// L4890
    bool v3120 = v3111 & v3119;	// L4891
    if (v3120) {	// L4892
      grant2 = 0;	// L4893
    }
    int32_t v3121 = pc2;	// L4895
    bool v3122 = v3121 >= 0;	// L4896
    int32_t v3123 = raw2;	// L4897
    bool v3124 = v3123 == 1;	// L4898
    int32_t v3125 = is_cond2;	// L4899
    bool v3126 = v3125 == 1;	// L4900
    int32_t v3127 = cmp_busy2;	// L4901
    bool v3128 = v3127 == 1;	// L4902
    bool v3129 = v3126 & v3128;	// L4903
    bool v3130 = v3124 | v3129;	// L4904
    bool v3131 = v3122 & v3130;	// L4905
    if (v3131) {	// L4906
      grant2 = 0;	// L4907
    }
    int32_t v3132 = retire_ok2;	// L4909
    bool v3133 = v3132 == 0;	// L4910
    if (v3133) {	// L4911
      grant2 = 0;	// L4912
    }
    int32_t v3134 = grant2;	// L4914
    bool v3135 = v3134 == 1;	// L4915
    if (v3135) {	// L4916
      int8_t v3136 = instr_cnt2;	// L4917
      int32_t v3137 = cfg_isz2;	// L4918
      int32_t v3138 = v3136;	// L4919
      bool v3139 = v3138 == v3137;	// L4920
      if (v3139) {	// L4921
        instr_cnt2 = 0;	// L4922
        int8_t v3140 = iter_cnt2;	// L4923
        int32_t v3141 = cfg_itsz2;	// L4924
        ac_int<33, true> v3142 = v3141;	// L4925
        ac_int<33, true> v3143 = v3142 - 1;	// L4926
        ac_int<33, true> v3144 = v3140;	// L4927
        bool v3145 = v3144 == v3143;	// L4928
        if (v3145) {	// L4929
          fetch_en2 = 0;	// L4930
        } else {
          int8_t v3146 = iter_cnt2;	// L4932
          ac_int<33, true> v3147 = v3146;	// L4933
          ac_int<33, true> v3148 = v3147 + 1;	// L4934
          uint8_t v3149 = v3148;	// L4935
          iter_cnt2 = v3149;	// L4936
        }
      } else {
        int8_t v3150 = instr_cnt2;	// L4939
        ac_int<33, true> v3151 = v3150;	// L4940
        ac_int<33, true> v3152 = v3151 + 1;	// L4941
        uint8_t v3153 = v3152;	// L4942
        instr_cnt2 = v3153;	// L4943
      }
    }
    int32_t c12;	// L4946
    c12 = -1;	// L4947
    int32_t c22;	// L4948
    c22 = -1;	// L4949
    int32_t v3156 = grant2;	// L4950
    bool v3157 = v3156 == 1;	// L4951
    int32_t v3158 = s12;	// L4952
    bool v3159 = v3158 >= 12;	// L4953
    bool v3160 = v3157 & v3159;	// L4954
    if (v3160) {	// L4955
      int32_t v3161 = s12;	// L4956
      int32_t v3162 = v3161 & 3;	// L4957
      c12 = v3162;	// L4958
    }
    int32_t v3163 = grant2;	// L4960
    bool v3164 = v3163 == 1;	// L4961
    int32_t v3165 = s22;	// L4962
    bool v3166 = v3165 >= 12;	// L4963
    bool v3167 = v3164 & v3166;	// L4964
    if (v3167) {	// L4965
      int32_t v3168 = s22;	// L4966
      int32_t v3169 = v3168 & 3;	// L4967
      c22 = v3169;	// L4968
    }
    int32_t v3170 = c12;	// L4970
    bool v3171 = v3170 >= 0;	// L4971
    if (v3171) {	// L4972
      int32_t v3172 = c12;	// L4973
      int v3173 = v3172;	// L4974
      half v3174 = hold_v2[v3173][1];	// L4975
      hold_v2[v3173][0] = v3174;	// L4978
      int32_t v3175 = c12;	// L4979
      int v3176 = v3175;	// L4980
      uint8_t v3177 = hold_cnt2[v3176];	// L4981
      ac_int<33, true> v3178 = v3177;	// L4982
      ac_int<33, true> v3179 = v3178 - 1;	// L4983
      uint8_t v3180 = v3179;	// L4984
      hold_cnt2[v3176] = v3180;	// L4987
    }
    int32_t v3181 = c22;	// L4989
    bool v3182 = v3181 >= 0;	// L4990
    int32_t v3183 = c12;	// L4992
    bool v3184 = v3181 != v3183;	// L4993
    bool v3185 = v3182 & v3184;	// L4994
    if (v3185) {	// L4995
      int32_t v3186 = c22;	// L4996
      int v3187 = v3186;	// L4997
      half v3188 = hold_v2[v3187][1];	// L4998
      hold_v2[v3187][0] = v3188;	// L5001
      int32_t v3189 = c22;	// L5002
      int v3190 = v3189;	// L5003
      uint8_t v3191 = hold_cnt2[v3190];	// L5004
      ac_int<33, true> v3192 = v3191;	// L5005
      ac_int<33, true> v3193 = v3192 - 1;	// L5006
      uint8_t v3194 = v3193;	// L5007
      hold_cnt2[v3190] = v3194;	// L5010
    }
    l_S_d_7_d14: for (int d14 = 0; d14 < 4; d14++) {	// L5012
      sc_r2[d14] = 0;	// L5013
    }
    int32_t v3196 = c12;	// L5015
    bool v3197 = v3196 >= 0;	// L5016
    if (v3197) {	// L5017
      int32_t v3198 = c12;	// L5018
      int v3199 = v3198;	// L5019
      sc_r2[v3199] = 1;	// L5020
    }
    int32_t v3200 = c22;	// L5022
    bool v3201 = v3200 >= 0;	// L5023
    int32_t v3202 = c12;	// L5025
    bool v3203 = v3200 != v3202;	// L5026
    bool v3204 = v3201 & v3203;	// L5027
    if (v3204) {	// L5028
      int32_t v3205 = c22;	// L5029
      int v3206 = v3205;	// L5030
      sc_r2[v3206] = 1;	// L5031
    }
    int32_t v3207 = grant2;	// L5033
    bool v3208 = v3207 == 1;	// L5034
    int32_t v3209 = s12;	// L5035
    bool v3210 = v3209 < 8;	// L5036
    int32_t v3211 = dsmask2;	// L5037
    int32_t v3212 = v3211 >> v3209;	// L5039
    int32_t v3213 = v3212 & 1;	// L5040
    bool v3214 = v3213 == 1;	// L5041
    bool v3215 = v3208 & v3210;	// L5042
    bool v3216 = v3215 & v3214;	// L5043
    if (v3216) {	// L5044
      int32_t v3217 = s12;	// L5045
      int v3218 = v3217;	// L5046
      drf_full2[v3218] = 0;	// L5047
    }
    int32_t v3219 = grant2;	// L5049
    bool v3220 = v3219 == 1;	// L5050
    int32_t v3221 = s22;	// L5051
    bool v3222 = v3221 < 8;	// L5052
    int32_t v3223 = dsmask2;	// L5053
    int32_t v3224 = v3223 >> v3221;	// L5055
    int32_t v3225 = v3224 & 1;	// L5056
    bool v3226 = v3225 == 1;	// L5057
    bool v3227 = v3220 & v3222;	// L5058
    bool v3228 = v3227 & v3226;	// L5059
    if (v3228) {	// L5060
      int32_t v3229 = s22;	// L5061
      int v3230 = v3229;	// L5062
      drf_full2[v3230] = 0;	// L5063
    }
    half res2;	// L5065
    res2 = (double)0.000000;	// L5066
    int32_t v3232 = op2;	// L5067
    bool v3233 = v3232 == 0;	// L5068
    if (v3233) {	// L5069
      half v3234 = a2;	// L5070
      half v3235 = b2;	// L5071
      half v3236 = v3234 + v3235;	// L5072
      res2 = v3236;	// L5073
    } else {
      int32_t v3237 = op2;	// L5075
      bool v3238 = v3237 == 1;	// L5076
      if (v3238) {	// L5077
        half v3239 = a2;	// L5078
        half v3240 = b2;	// L5079
        half v3241 = v3239 - v3240;	// L5080
        res2 = v3241;	// L5081
      } else {
        int32_t v3242 = op2;	// L5083
        bool v3243 = v3242 == 2;	// L5084
        if (v3243) {	// L5085
          half v3244 = a2;	// L5086
          half v3245 = b2;	// L5087
          half v3246 = v3244 * v3245;	// L5088
          res2 = v3246;	// L5089
        } else {
          int32_t v3247 = op2;	// L5091
          bool v3248 = v3247 == 8;	// L5092
          if (v3248) {	// L5093
            half v3249 = a2;	// L5094
            half v3250 = b2;	// L5095
            bool v3251 = v3249 >= v3250;	// L5096
            if (v3251) {	// L5097
              res2 = (double)1.000000;	// L5098
            } else {
              res2 = (double)-1.000000;	// L5100
            }
          } else {
            int32_t v3252 = op2;	// L5103
            bool v3253 = v3252 == 9;	// L5104
            if (v3253) {	// L5105
              half v3254 = a2;	// L5106
              half v3255 = b2;	// L5107
              bool v3256 = v3254 < v3255;	// L5108
              if (v3256) {	// L5109
                res2 = (double)1.000000;	// L5110
              } else {
                res2 = (double)-1.000000;	// L5112
              }
            } else {
              half v3257 = a2;	// L5115
              res2 = v3257;	// L5116
            }
          }
        }
      }
    }
    int32_t v3258 = a_vld2;	// L5122
    int32_t res_vld2;	// L5123
    res_vld2 = v3258;	// L5124
    int32_t v3260 = op2;	// L5125
    bool v3261 = v3260 == 0;	// L5126
    bool v3262 = v3260 == 1;	// L5128
    bool v3263 = v3260 == 2;	// L5130
    bool v3264 = v3260 == 8;	// L5132
    bool v3265 = v3260 == 9;	// L5134
    bool v3266 = v3261 | v3262;	// L5135
    bool v3267 = v3266 | v3263;	// L5136
    bool v3268 = v3267 | v3264;	// L5137
    bool v3269 = v3268 | v3265;	// L5138
    if (v3269) {	// L5139
      int32_t v3270 = a_vld2;	// L5140
      int32_t v3271 = b_vld2;	// L5141
      int64_t v3272 = v3270;	// L5142
      int64_t v3273 = v3271;	// L5143
      int64_t v3274 = v3272 * v3273;	// L5144
      int32_t v3275 = v3274;	// L5145
      res_vld2 = v3275;	// L5146
    }
    int32_t v3276 = grant2;	// L5148
    bool v3277 = v3276 == 0;	// L5149
    if (v3277) {	// L5150
      res_vld2 = 0;	// L5151
    }
    int32_t is_rtr2;	// L5153
    is_rtr2 = 0;	// L5154
    int32_t v3279 = op2;	// L5155
    bool v3280 = v3279 >= 4;	// L5156
    ac_int<33, true> v3281 = v3279;	// L5158
    bool v3282 = v3281 <= 7;	// L5159
    bool v3283 = v3280 & v3282;	// L5160
    if (v3283) {	// L5161
      is_rtr2 = 1;	// L5162
    }
    int32_t v3284 = retire_ok2;	// L5164
    bool v3285 = v3284 == 1;	// L5165
    if (v3285) {	// L5166
      l_S_k_8_k5: for (int k5 = 0; k5 < 4; k5++) {	// L5167
        uint8_t v3287 = sb_v2[(k5 + 1)];	// L5168
        sb_v2[k5] = v3287;	// L5169
        uint8_t v3288 = sb_dst2[(k5 + 1)];	// L5170
        sb_dst2[k5] = v3288;	// L5171
        uint8_t v3289 = sb_cmp2[(k5 + 1)];	// L5172
        sb_cmp2[k5] = v3289;	// L5173
        uint8_t v3290 = sb_rtr2[(k5 + 1)];	// L5174
        sb_rtr2[k5] = v3290;	// L5175
        uint8_t v3291 = sb_inj2[(k5 + 1)];	// L5176
        sb_inj2[k5] = v3291;	// L5177
        uint8_t v3292 = sb_dir2[(k5 + 1)];	// L5178
        sb_dir2[k5] = v3292;	// L5179
        uint8_t v3293 = sb_id2[(k5 + 1)];	// L5180
        sb_id2[k5] = v3293;	// L5181
        uint8_t v3294 = sb_rvld2[(k5 + 1)];	// L5182
        sb_rvld2[k5] = v3294;	// L5183
        uint8_t v3295 = sb_ix2[(k5 + 1)];	// L5184
        sb_ix2[k5] = v3295;	// L5185
        uint8_t v3296 = sb_long2[(k5 + 1)];	// L5186
        sb_long2[k5] = v3296;	// L5187
      }
      sb_v2[4] = 0;	// L5189
    }
    int32_t v3297 = grant2;	// L5191
    bool v3298 = v3297 == 1;	// L5192
    if (v3298) {	// L5193
      half v3299 = res2;	// L5194
      int8_t v3300 = resq_wr2;	// L5195
      int v3301 = v3300;	// L5196
      resq2[v3301] = v3299;	// L5197
      int32_t cq2;	// L5198
      cq2 = 0;	// L5199
      int32_t v3303 = op2;	// L5200
      bool v3304 = v3303 == 8;	// L5201
      if (v3304) {	// L5202
        half v3305 = a2;	// L5203
        half v3306 = b2;	// L5204
        bool v3307 = v3305 >= v3306;	// L5205
        if (v3307) {	// L5206
          cq2 = 1;	// L5207
        }
      }
      int32_t v3308 = op2;	// L5210
      bool v3309 = v3308 == 9;	// L5211
      if (v3309) {	// L5212
        half v3310 = a2;	// L5213
        half v3311 = b2;	// L5214
        bool v3312 = v3310 < v3311;	// L5215
        if (v3312) {	// L5216
          cq2 = 1;	// L5217
        }
      }
      int32_t v3313 = cq2;	// L5220
      uint8_t v3314 = v3313;	// L5221
      int8_t v3315 = resq_wr2;	// L5222
      int v3316 = v3315;	// L5223
      cmpq2[v3316] = v3314;	// L5224
      sb_v2[4] = 1;	// L5225
      int32_t v3317 = dst2;	// L5226
      uint8_t v3318 = v3317;	// L5227
      sb_dst2[4] = v3318;	// L5228
      int8_t v3319 = resq_wr2;	// L5229
      sb_ix2[4] = v3319;	// L5230
      int32_t v3320 = binop2;	// L5231
      uint8_t v3321 = v3320;	// L5232
      sb_long2[4] = v3321;	// L5233
      sb_cmp2[4] = 0;	// L5234
      int32_t v3322 = op2;	// L5235
      bool v3323 = v3322 == 8;	// L5236
      bool v3324 = v3322 == 9;	// L5238
      bool v3325 = v3323 | v3324;	// L5239
      if (v3325) {	// L5240
        sb_cmp2[4] = 1;	// L5241
      }
      int32_t v3326 = is_rtr2;	// L5243
      int32_t rtrf2;	// L5244
      rtrf2 = v3326;	// L5245
      int32_t v3328 = is_cond2;	// L5246
      bool v3329 = v3328 == 1;	// L5247
      if (v3329) {	// L5248
        rtrf2 = 1;	// L5249
      }
      int32_t v3330 = rtrf2;	// L5251
      uint8_t v3331 = v3330;	// L5252
      sb_rtr2[4] = v3331;	// L5253
      int32_t v3332 = is_rtr2;	// L5254
      int32_t inj2;	// L5255
      inj2 = v3332;	// L5256
      int32_t v3334 = is_cond2;	// L5257
      bool v3335 = v3334 == 1;	// L5258
      int8_t v3336 = condition_reg2;	// L5259
      int32_t v3337 = v3336;	// L5260
      bool v3338 = v3337 == 1;	// L5261
      bool v3339 = v3335 & v3338;	// L5262
      if (v3339) {	// L5263
        inj2 = 1;	// L5264
      }
      int32_t v3340 = inj2;	// L5266
      uint8_t v3341 = v3340;	// L5267
      sb_inj2[4] = v3341;	// L5268
      int32_t v3342 = op2;	// L5269
      int32_t v3343 = v3342 & 3;	// L5270
      uint8_t v3344 = v3343;	// L5271
      sb_dir2[4] = v3344;	// L5272
      int32_t v3345 = s22;	// L5273
      uint8_t v3346 = v3345;	// L5274
      sb_id2[4] = v3346;	// L5275
      int32_t v3347 = res_vld2;	// L5276
      uint8_t v3348 = v3347;	// L5277
      sb_rvld2[4] = v3348;	// L5278
      int8_t v3349 = resq_wr2;	// L5279
      ac_int<33, true> v3350 = v3349;	// L5280
      ac_int<33, true> v3351 = v3350 + 1;	// L5281
      ac_int<33, true> v3352 = v3351 & 7;	// L5282
      uint8_t v3353 = v3352;	// L5283
      resq_wr2 = v3353;	// L5284
    }
    txn_r2 = 0;	// L5286
    txs_r2 = 0;	// L5287
    txw_r2 = 0;	// L5288
    txe_r2 = 0;	// L5289
    int32_t v3354 = txp_v2[0];	// L5290
    bool v3355 = v3354 == 1;	// L5291
    int32_t v3356 = scred2[0];	// L5292
    bool v3357 = v3356 > 0;	// L5293
    bool v3358 = v3355 & v3357;	// L5294
    if (v3358) {	// L5295
      ac_int<17, false> twn2;	// L5296
      twn2 = 0;	// L5297
      ac_int<17, true> v3360 = twn2;	// L5298
      ac_int<17, true> v3361;
      ap_int<17> v3361_tmp = v3360;
      v3361_tmp[0] = 1;      v3361 = v3361_tmp;	// L5299
      twn2 = v3361;	// L5300
      half v3362 = txp_d2[0];	// L5301
      uint16_t v3363;
      union { half from; uint16_t to;} _converter_v3362_to_v3363 = {};
      _converter_v3362_to_v3363.from = v3362;
      v3363 = _converter_v3362_to_v3363.to;	// L5302
      ac_int<17, true> v3364 = twn2;	// L5303
      ac_int<17, true> v3365;
      ap_int<17> v3365_tmp = v3364;
      v3365_tmp(16, 1) = v3363;
      v3365 = v3365_tmp;	// L5304
      twn2 = v3365;	// L5305
      ac_int<17, true> v3366 = twn2;	// L5306
      txn_r2 = v3366;	// L5307
      txp_v2[0] = 0;	// L5308
      int32_t v3367 = scred2[0];	// L5309
      ac_int<33, true> v3368 = v3367;	// L5310
      ac_int<33, true> v3369 = v3368 - 1;	// L5311
      int32_t v3370 = v3369;	// L5312
      scred2[0] = v3370;	// L5313
    }
    int32_t v3371 = txp_v2[1];	// L5315
    bool v3372 = v3371 == 1;	// L5316
    int32_t v3373 = scred2[1];	// L5317
    bool v3374 = v3373 > 0;	// L5318
    bool v3375 = v3372 & v3374;	// L5319
    if (v3375) {	// L5320
      ac_int<17, false> tws2;	// L5321
      tws2 = 0;	// L5322
      ac_int<17, true> v3377 = tws2;	// L5323
      ac_int<17, true> v3378;
      ap_int<17> v3378_tmp = v3377;
      v3378_tmp[0] = 1;      v3378 = v3378_tmp;	// L5324
      tws2 = v3378;	// L5325
      half v3379 = txp_d2[1];	// L5326
      uint16_t v3380;
      union { half from; uint16_t to;} _converter_v3379_to_v3380 = {};
      _converter_v3379_to_v3380.from = v3379;
      v3380 = _converter_v3379_to_v3380.to;	// L5327
      ac_int<17, true> v3381 = tws2;	// L5328
      ac_int<17, true> v3382;
      ap_int<17> v3382_tmp = v3381;
      v3382_tmp(16, 1) = v3380;
      v3382 = v3382_tmp;	// L5329
      tws2 = v3382;	// L5330
      ac_int<17, true> v3383 = tws2;	// L5331
      txs_r2 = v3383;	// L5332
      txp_v2[1] = 0;	// L5333
      int32_t v3384 = scred2[1];	// L5334
      ac_int<33, true> v3385 = v3384;	// L5335
      ac_int<33, true> v3386 = v3385 - 1;	// L5336
      int32_t v3387 = v3386;	// L5337
      scred2[1] = v3387;	// L5338
    }
    int32_t v3388 = txp_v2[2];	// L5340
    bool v3389 = v3388 == 1;	// L5341
    int32_t v3390 = scred2[2];	// L5342
    bool v3391 = v3390 > 0;	// L5343
    bool v3392 = v3389 & v3391;	// L5344
    if (v3392) {	// L5345
      ac_int<17, false> tww2;	// L5346
      tww2 = 0;	// L5347
      ac_int<17, true> v3394 = tww2;	// L5348
      ac_int<17, true> v3395;
      ap_int<17> v3395_tmp = v3394;
      v3395_tmp[0] = 1;      v3395 = v3395_tmp;	// L5349
      tww2 = v3395;	// L5350
      half v3396 = txp_d2[2];	// L5351
      uint16_t v3397;
      union { half from; uint16_t to;} _converter_v3396_to_v3397 = {};
      _converter_v3396_to_v3397.from = v3396;
      v3397 = _converter_v3396_to_v3397.to;	// L5352
      ac_int<17, true> v3398 = tww2;	// L5353
      ac_int<17, true> v3399;
      ap_int<17> v3399_tmp = v3398;
      v3399_tmp(16, 1) = v3397;
      v3399 = v3399_tmp;	// L5354
      tww2 = v3399;	// L5355
      ac_int<17, true> v3400 = tww2;	// L5356
      txw_r2 = v3400;	// L5357
      txp_v2[2] = 0;	// L5358
      int32_t v3401 = scred2[2];	// L5359
      ac_int<33, true> v3402 = v3401;	// L5360
      ac_int<33, true> v3403 = v3402 - 1;	// L5361
      int32_t v3404 = v3403;	// L5362
      scred2[2] = v3404;	// L5363
    }
    int32_t v3405 = txp_v2[3];	// L5365
    bool v3406 = v3405 == 1;	// L5366
    int32_t v3407 = scred2[3];	// L5367
    bool v3408 = v3407 > 0;	// L5368
    bool v3409 = v3406 & v3408;	// L5369
    if (v3409) {	// L5370
      ac_int<17, false> twe2;	// L5371
      twe2 = 0;	// L5372
      ac_int<17, true> v3411 = twe2;	// L5373
      ac_int<17, true> v3412;
      ap_int<17> v3412_tmp = v3411;
      v3412_tmp[0] = 1;      v3412 = v3412_tmp;	// L5374
      twe2 = v3412;	// L5375
      half v3413 = txp_d2[3];	// L5376
      uint16_t v3414;
      union { half from; uint16_t to;} _converter_v3413_to_v3414 = {};
      _converter_v3413_to_v3414.from = v3413;
      v3414 = _converter_v3413_to_v3414.to;	// L5377
      ac_int<17, true> v3415 = twe2;	// L5378
      ac_int<17, true> v3416;
      ap_int<17> v3416_tmp = v3415;
      v3416_tmp(16, 1) = v3414;
      v3416 = v3416_tmp;	// L5379
      twe2 = v3416;	// L5380
      ac_int<17, true> v3417 = twe2;	// L5381
      txe_r2 = v3417;	// L5382
      txp_v2[3] = 0;	// L5383
      int32_t v3418 = scred2[3];	// L5384
      ac_int<33, true> v3419 = v3418;	// L5385
      ac_int<33, true> v3420 = v3419 - 1;	// L5386
      int32_t v3421 = v3420;	// L5387
      scred2[3] = v3421;	// L5388
    }
    int32_t v3422 = crv_vld2;	// L5390
    bool v3423 = v3422 == 1;	// L5391
    if (v3423) {	// L5392
      int32_t v3424 = crv_mode2;	// L5393
      bool v3425 = v3424 == 1;	// L5394
      if (v3425) {	// L5395
        int32_t v3426 = crv_addr2;	// L5396
        int32_t v3427 = v3426 >> 3;	// L5397
        int32_t v3428 = v3427 & 1;	// L5398
        bool v3429 = v3428 == 1;	// L5399
        if (v3429) {	// L5400
          int32_t v3430 = crv_raw2;	// L5401
          int32_t v3431 = crv_addr2;	// L5402
          int32_t v3432 = v3431 & 7;	// L5403
          int v3433 = v3432;	// L5404
          irf2[v3433] = v3430;	// L5405
        } else {
          int32_t v3434 = crv_addr2;	// L5407
          bool v3435 = v3434 == 0;	// L5408
          if (v3435) {	// L5409
            int32_t v3436 = crv_raw2;	// L5410
            int32_t v3437 = v3436 & 255;	// L5411
            dsmask2 = v3437;	// L5412
            int32_t v3438 = crv_raw2;	// L5413
            int32_t v3439 = v3438 >> 8;	// L5414
            int32_t v3440 = v3439 & 7;	// L5415
            cfg_isz2 = v3440;	// L5416
            int32_t v3441 = crv_raw2;	// L5417
            int32_t v3442 = v3441 >> 15;	// L5418
            int32_t v3443 = v3442 & 1;	// L5419
            bool v3444 = v3443 == 1;	// L5420
            if (v3444) {	// L5421
              fetch_en2 = 1;	// L5422
              instr_cnt2 = 0;	// L5423
              iter_cnt2 = 0;	// L5424
            }
          } else {
            int32_t v3445 = crv_addr2;	// L5427
            bool v3446 = v3445 == 1;	// L5428
            if (v3446) {	// L5429
              int32_t v3447 = crv_raw2;	// L5430
              int32_t v3448 = v3447 & 255;	// L5431
              cfg_itsz2 = v3448;	// L5432
            }
          }
        }
      } else {
        int32_t v3449 = crv_addr2;	// L5437
        int32_t v3450 = v3449 >> 2;	// L5438
        int32_t v3451 = v3450 & 3;	// L5439
        bool v3452 = v3451 == 3;	// L5440
        if (v3452) {	// L5441
          int32_t v3453 = crv_addr2;	// L5442
          int32_t v3454 = v3453 & 3;	// L5443
          int v3455 = v3454;	// L5444
          txp_v2[v3455] = 1;	// L5445
          half v3456 = crv_data2;	// L5446
          int32_t v3457 = crv_addr2;	// L5447
          int32_t v3458 = v3457 & 3;	// L5448
          int v3459 = v3458;	// L5449
          txp_d2[v3459] = v3456;	// L5450
          int32_t v3460 = crv_addr2;	// L5451
          int32_t v3461 = v3460 & 3;	// L5452
          int v3462 = v3461;	// L5453
          txp_r2[v3462] = 1;	// L5454
        } else {
          int32_t v3463 = crv_addr2;	// L5456
          bool v3464 = v3463 < 8;	// L5457
          int32_t v3465 = dsmask2;	// L5458
          int32_t v3466 = v3465 >> v3463;	// L5460
          int32_t v3467 = v3466 & 1;	// L5461
          bool v3468 = v3467 == 1;	// L5462
          bool v3469 = v3464 & v3468;	// L5463
          if (v3469) {	// L5464
            int32_t v3470 = crv_addr2;	// L5465
            int v3471 = v3470;	// L5466
            int32_t v3472 = drf_full2[v3471];	// L5467
            bool v3473 = v3472 == 0;	// L5468
            if (v3473) {	// L5469
              half v3474 = crv_data2;	// L5470
              int32_t v3475 = crv_addr2;	// L5471
              int v3476 = v3475;	// L5472
              drf2[v3476] = v3474;	// L5473
              int32_t v3477 = crv_addr2;	// L5474
              int v3478 = v3477;	// L5475
              drf_full2[v3478] = 1;	// L5476
            }
          } else {
            half v3479 = crv_data2;	// L5479
            int32_t v3480 = crv_addr2;	// L5480
            int v3481 = v3480;	// L5481
            drf2[v3481] = v3479;	// L5482
          }
        }
      }
    }
    ac_int<26, true> v3482 = oe_r2;	// L5487
    v2332.write(v3482);	// L5488
    ac_int<26, true> v3483 = ow_r2;	// L5489
    v2333.write(v3483);	// L5490
    ac_int<26, true> v3484 = os_r2;	// L5491
    v2334.write(v3484);	// L5492
    ac_int<26, true> v3485 = on_r2;	// L5493
    v2335.write(v3485);	// L5494
    ac_int<17, true> v3486 = txe_r2;	// L5495
    v2336.write(v3486);	// L5496
    ac_int<17, true> v3487 = txw_r2;	// L5497
    v2337.write(v3487);	// L5498
    ac_int<17, true> v3488 = txs_r2;	// L5499
    v2338.write(v3488);	// L5500
    ac_int<17, true> v3489 = txn_r2;	// L5501
    v2339.write(v3489);	// L5502
    int8_t v3490 = cre_r2;	// L5503
    v2340.write(v3490);	// L5504
    int8_t v3491 = crw_r2;	// L5505
    v2341.write(v3491);	// L5506
    int8_t v3492 = crs_r2;	// L5507
    v2342.write(v3492);	// L5508
    int8_t v3493 = crn_r2;	// L5509
    v2343.write(v3493);	// L5510
    int32_t v3494 = sc_r2[0];	// L5511
    v2346.write(v3494);	// L5512
    int32_t v3495 = sc_r2[1];	// L5513
    v2347.write(v3495);	// L5514
    int32_t v3496 = sc_r2[2];	// L5515
    v2344.write(v3496);	// L5516
    int32_t v3497 = sc_r2[3];	// L5517
    v2345.write(v3497);	// L5518
  }
}

void node_1_1(
  ac_channel< ac_int<26, false> >& v3498,
  ac_channel< ac_int<26, false> >& v3499,
  ac_channel< ac_int<26, false> >& v3500,
  ac_channel< ac_int<26, false> >& v3501,
  ac_channel< ac_int<17, false> >& v3502,
  ac_channel< ac_int<17, false> >& v3503,
  ac_channel< ac_int<17, false> >& v3504,
  ac_channel< ac_int<17, false> >& v3505,
  ac_channel< int32_t >& v3506,
  ac_channel< int32_t >& v3507,
  ac_channel< int32_t >& v3508,
  ac_channel< int32_t >& v3509,
  ac_channel< int32_t >& v3510,
  ac_channel< int32_t >& v3511,
  ac_channel< int32_t >& v3512,
  ac_channel< int32_t >& v3513,
  ac_channel< ac_int<26, false> >& v3514,
  ac_channel< ac_int<26, false> >& v3515,
  ac_channel< ac_int<26, false> >& v3516,
  ac_channel< ac_int<26, false> >& v3517,
  ac_channel< int32_t >& v3518,
  ac_channel< int32_t >& v3519,
  ac_channel< int32_t >& v3520,
  ac_channel< int32_t >& v3521,
  ac_channel< int32_t >& v3522,
  ac_channel< int32_t >& v3523,
  ac_channel< int32_t >& v3524,
  ac_channel< int32_t >& v3525,
  ac_channel< ac_int<17, false> >& v3526,
  ac_channel< ac_int<17, false> >& v3527,
  ac_channel< ac_int<17, false> >& v3528,
  ac_channel< ac_int<17, false> >& v3529
) {	// L5522
  int32_t irf3[8];	// L5559
  for (int v3531 = 0; v3531 < 8; v3531++) {	// L5560
    irf3[v3531] = 0;	// L5560
  }
  half drf3[8];	// L5561
  for (int v3533 = 0; v3533 < 8; v3533++) {	// L5562
    drf3[v3533] = (double)0.000000;	// L5562
  }
  int32_t drf_full3[8];	// L5563
  for (int v3535 = 0; v3535 < 8; v3535++) {	// L5564
    drf_full3[v3535] = 0;	// L5564
  }
  int32_t dsmask3;	// L5565
  dsmask3 = 0;	// L5566
  int32_t crv_vld3;	// L5567
  crv_vld3 = 0;	// L5568
  half crv_data3;	// L5569
  crv_data3 = (double)0.000000;	// L5570
  int32_t crv_addr3;	// L5571
  crv_addr3 = 0;	// L5572
  int32_t crv_mode3;	// L5573
  crv_mode3 = 0;	// L5574
  int32_t crv_raw3;	// L5575
  crv_raw3 = 0;	// L5576
  int32_t csd_vld3;	// L5577
  csd_vld3 = 0;	// L5578
  ac_int<26, false> csd_pkt3;	// L5579
  csd_pkt3 = 0;	// L5580
  int32_t csd_dir3;	// L5581
  csd_dir3 = 0;	// L5582
  int32_t row_id3;	// L5583
  row_id3 = 1;	// L5584
  int32_t col_id3;	// L5585
  col_id3 = 1;	// L5586
  ac_int<26, false> oe_r3;	// L5587
  oe_r3 = 0;	// L5588
  ac_int<26, false> ow_r3;	// L5589
  ow_r3 = 0;	// L5590
  ac_int<26, false> on_r3;	// L5591
  on_r3 = 0;	// L5592
  ac_int<26, false> os_r3;	// L5593
  os_r3 = 0;	// L5594
  ac_int<17, false> txn_r3;	// L5595
  txn_r3 = 0;	// L5596
  ac_int<17, false> txs_r3;	// L5597
  txs_r3 = 0;	// L5598
  ac_int<17, false> txw_r3;	// L5599
  txw_r3 = 0;	// L5600
  ac_int<17, false> txe_r3;	// L5601
  txe_r3 = 0;	// L5602
  half hold_v3[4][2];	// L5603
  for (int v3556 = 0; v3556 < 4; v3556++) {	// L5604
    for (int v3557 = 0; v3557 < 2; v3557++) {	// L5604
      hold_v3[v3556][v3557] = (double)0.000000;	// L5604
    }
  }
  uint8_t hold_cnt3[4];	// L5605
  for (int v3559 = 0; v3559 < 4; v3559++) {	// L5606
    hold_cnt3[v3559] = 0;	// L5606
  }
  ac_int<26, false> rbuf3[4][2];	// L5607
  for (int v3561 = 0; v3561 < 4; v3561++) {	// L5608
    for (int v3562 = 0; v3562 < 2; v3562++) {	// L5608
      rbuf3[v3561][v3562] = 0;	// L5608
    }
  }
  uint8_t rbcnt3[4];	// L5609
  for (int v3564 = 0; v3564 < 4; v3564++) {	// L5610
    rbcnt3[v3564] = 0;	// L5610
  }
  uint8_t rcred3[4];	// L5611
  for (int v3566 = 0; v3566 < 4; v3566++) {	// L5612
    rcred3[v3566] = 0;	// L5612
  }
  uint8_t cre_r3;	// L5613
  cre_r3 = 2;	// L5614
  uint8_t crw_r3;	// L5615
  crw_r3 = 2;	// L5616
  uint8_t crs_r3;	// L5617
  crs_r3 = 2;	// L5618
  uint8_t crn_r3;	// L5619
  crn_r3 = 2;	// L5620
  int32_t scred3[4];	// L5621
  for (int v3572 = 0; v3572 < 4; v3572++) {	// L5622
    scred3[v3572] = 0;	// L5622
  }
  int32_t txp_v3[4];	// L5623
  for (int v3574 = 0; v3574 < 4; v3574++) {	// L5624
    txp_v3[v3574] = 0;	// L5624
  }
  half txp_d3[4];	// L5625
  for (int v3576 = 0; v3576 < 4; v3576++) {	// L5626
    txp_d3[v3576] = (double)0.000000;	// L5626
  }
  int32_t txp_r3[4];	// L5627
  for (int v3578 = 0; v3578 < 4; v3578++) {	// L5628
    txp_r3[v3578] = 0;	// L5628
  }
  int32_t sc_r3[4];	// L5629
  for (int v3580 = 0; v3580 < 4; v3580++) {	// L5630
    sc_r3[v3580] = 2;	// L5630
  }
  int32_t cfg_isz3;	// L5631
  cfg_isz3 = 0;	// L5632
  int32_t cfg_itsz3;	// L5633
  cfg_itsz3 = 0;	// L5634
  uint8_t fetch_en3;	// L5635
  fetch_en3 = 0;	// L5636
  uint8_t instr_cnt3;	// L5637
  instr_cnt3 = 0;	// L5638
  uint8_t iter_cnt3;	// L5639
  iter_cnt3 = 0;	// L5640
  uint8_t condition_reg3;	// L5641
  condition_reg3 = 0;	// L5642
  uint8_t sb_v3[5];	// L5643
  for (int v3588 = 0; v3588 < 5; v3588++) {	// L5644
    sb_v3[v3588] = 0;	// L5644
  }
  uint8_t sb_dst3[5];	// L5645
  for (int v3590 = 0; v3590 < 5; v3590++) {	// L5646
    sb_dst3[v3590] = 0;	// L5646
  }
  uint8_t sb_cmp3[5];	// L5647
  for (int v3592 = 0; v3592 < 5; v3592++) {	// L5648
    sb_cmp3[v3592] = 0;	// L5648
  }
  uint8_t sb_rtr3[5];	// L5649
  for (int v3594 = 0; v3594 < 5; v3594++) {	// L5650
    sb_rtr3[v3594] = 0;	// L5650
  }
  uint8_t sb_inj3[5];	// L5651
  for (int v3596 = 0; v3596 < 5; v3596++) {	// L5652
    sb_inj3[v3596] = 0;	// L5652
  }
  uint8_t sb_dir3[5];	// L5653
  for (int v3598 = 0; v3598 < 5; v3598++) {	// L5654
    sb_dir3[v3598] = 0;	// L5654
  }
  uint8_t sb_id3[5];	// L5655
  for (int v3600 = 0; v3600 < 5; v3600++) {	// L5656
    sb_id3[v3600] = 0;	// L5656
  }
  uint8_t sb_rvld3[5];	// L5657
  for (int v3602 = 0; v3602 < 5; v3602++) {	// L5658
    sb_rvld3[v3602] = 0;	// L5658
  }
  uint8_t sb_ix3[5];	// L5659
  for (int v3604 = 0; v3604 < 5; v3604++) {	// L5660
    sb_ix3[v3604] = 0;	// L5660
  }
  uint8_t sb_long3[5];	// L5661
  for (int v3606 = 0; v3606 < 5; v3606++) {	// L5662
    sb_long3[v3606] = 0;	// L5662
  }
  half resq3[8];	// L5663
  for (int v3608 = 0; v3608 < 8; v3608++) {	// L5664
    resq3[v3608] = (double)0.000000;	// L5664
  }
  uint8_t cmpq3[8];	// L5665
  for (int v3610 = 0; v3610 < 8; v3610++) {	// L5666
    cmpq3[v3610] = 0;	// L5666
  }
  uint8_t resq_wr3;	// L5667
  resq_wr3 = 0;	// L5668
  ac_int<26, false> zpkt3;	// L5669
  zpkt3 = 0;	// L5670
  ac_int<17, false> zsys3;	// L5671
  zsys3 = 0;	// L5672
  int32_t zcr3;	// L5673
  zcr3 = 0;	// L5674
  ac_int<26, true> v3615 = zpkt3;	// L5675
  v3498.write(v3615);	// L5676
  ac_int<26, true> v3616 = zpkt3;	// L5677
  v3499.write(v3616);	// L5678
  ac_int<26, true> v3617 = zpkt3;	// L5679
  v3500.write(v3617);	// L5680
  ac_int<26, true> v3618 = zpkt3;	// L5681
  v3501.write(v3618);	// L5682
  ac_int<17, true> v3619 = zsys3;	// L5683
  v3502.write(v3619);	// L5684
  ac_int<17, true> v3620 = zsys3;	// L5685
  v3503.write(v3620);	// L5686
  ac_int<17, true> v3621 = zsys3;	// L5687
  v3504.write(v3621);	// L5688
  ac_int<17, true> v3622 = zsys3;	// L5689
  v3505.write(v3622);	// L5690
  int32_t v3623 = zcr3;	// L5691
  v3506.write(v3623);	// L5692
  int32_t v3624 = zcr3;	// L5693
  v3507.write(v3624);	// L5694
  int32_t v3625 = zcr3;	// L5695
  v3508.write(v3625);	// L5696
  int32_t v3626 = zcr3;	// L5697
  v3509.write(v3626);	// L5698
  int32_t v3627 = zcr3;	// L5699
  v3510.write(v3627);	// L5700
  int32_t v3628 = zcr3;	// L5701
  v3511.write(v3628);	// L5702
  int32_t v3629 = zcr3;	// L5703
  v3512.write(v3629);	// L5704
  int32_t v3630 = zcr3;	// L5705
  v3513.write(v3630);	// L5706
  ac_int<26, true> v3631 = zpkt3;	// L5707
  v3498.write(v3631);	// L5708
  ac_int<26, true> v3632 = zpkt3;	// L5709
  v3499.write(v3632);	// L5710
  ac_int<26, true> v3633 = zpkt3;	// L5711
  v3500.write(v3633);	// L5712
  ac_int<26, true> v3634 = zpkt3;	// L5713
  v3501.write(v3634);	// L5714
  ac_int<17, true> v3635 = zsys3;	// L5715
  v3502.write(v3635);	// L5716
  ac_int<17, true> v3636 = zsys3;	// L5717
  v3503.write(v3636);	// L5718
  ac_int<17, true> v3637 = zsys3;	// L5719
  v3504.write(v3637);	// L5720
  ac_int<17, true> v3638 = zsys3;	// L5721
  v3505.write(v3638);	// L5722
  int32_t v3639 = zcr3;	// L5723
  v3506.write(v3639);	// L5724
  int32_t v3640 = zcr3;	// L5725
  v3507.write(v3640);	// L5726
  int32_t v3641 = zcr3;	// L5727
  v3508.write(v3641);	// L5728
  int32_t v3642 = zcr3;	// L5729
  v3509.write(v3642);	// L5730
  int32_t v3643 = zcr3;	// L5731
  v3510.write(v3643);	// L5732
  int32_t v3644 = zcr3;	// L5733
  v3511.write(v3644);	// L5734
  int32_t v3645 = zcr3;	// L5735
  v3512.write(v3645);	// L5736
  int32_t v3646 = zcr3;	// L5737
  v3513.write(v3646);	// L5738
  ac_int<26, true> v3647 = zpkt3;	// L5739
  v3498.write(v3647);	// L5740
  ac_int<26, true> v3648 = zpkt3;	// L5741
  v3499.write(v3648);	// L5742
  ac_int<26, true> v3649 = zpkt3;	// L5743
  v3500.write(v3649);	// L5744
  ac_int<26, true> v3650 = zpkt3;	// L5745
  v3501.write(v3650);	// L5746
  ac_int<17, true> v3651 = zsys3;	// L5747
  v3502.write(v3651);	// L5748
  ac_int<17, true> v3652 = zsys3;	// L5749
  v3503.write(v3652);	// L5750
  ac_int<17, true> v3653 = zsys3;	// L5751
  v3504.write(v3653);	// L5752
  ac_int<17, true> v3654 = zsys3;	// L5753
  v3505.write(v3654);	// L5754
  int32_t v3655 = zcr3;	// L5755
  v3506.write(v3655);	// L5756
  int32_t v3656 = zcr3;	// L5757
  v3507.write(v3656);	// L5758
  int32_t v3657 = zcr3;	// L5759
  v3508.write(v3657);	// L5760
  int32_t v3658 = zcr3;	// L5761
  v3509.write(v3658);	// L5762
  int32_t v3659 = zcr3;	// L5763
  v3510.write(v3659);	// L5764
  int32_t v3660 = zcr3;	// L5765
  v3511.write(v3660);	// L5766
  int32_t v3661 = zcr3;	// L5767
  v3512.write(v3661);	// L5768
  int32_t v3662 = zcr3;	// L5769
  v3513.write(v3662);	// L5770
  ac_int<26, true> v3663 = zpkt3;	// L5771
  v3498.write(v3663);	// L5772
  ac_int<26, true> v3664 = zpkt3;	// L5773
  v3499.write(v3664);	// L5774
  ac_int<26, true> v3665 = zpkt3;	// L5775
  v3500.write(v3665);	// L5776
  ac_int<26, true> v3666 = zpkt3;	// L5777
  v3501.write(v3666);	// L5778
  ac_int<17, true> v3667 = zsys3;	// L5779
  v3502.write(v3667);	// L5780
  ac_int<17, true> v3668 = zsys3;	// L5781
  v3503.write(v3668);	// L5782
  ac_int<17, true> v3669 = zsys3;	// L5783
  v3504.write(v3669);	// L5784
  ac_int<17, true> v3670 = zsys3;	// L5785
  v3505.write(v3670);	// L5786
  int32_t v3671 = zcr3;	// L5787
  v3506.write(v3671);	// L5788
  int32_t v3672 = zcr3;	// L5789
  v3507.write(v3672);	// L5790
  int32_t v3673 = zcr3;	// L5791
  v3508.write(v3673);	// L5792
  int32_t v3674 = zcr3;	// L5793
  v3509.write(v3674);	// L5794
  int32_t v3675 = zcr3;	// L5795
  v3510.write(v3675);	// L5796
  int32_t v3676 = zcr3;	// L5797
  v3511.write(v3676);	// L5798
  int32_t v3677 = zcr3;	// L5799
  v3512.write(v3677);	// L5800
  int32_t v3678 = zcr3;	// L5801
  v3513.write(v3678);	// L5802
  ac_int<26, true> v3679 = zpkt3;	// L5803
  v3498.write(v3679);	// L5804
  ac_int<26, true> v3680 = zpkt3;	// L5805
  v3499.write(v3680);	// L5806
  ac_int<26, true> v3681 = zpkt3;	// L5807
  v3500.write(v3681);	// L5808
  ac_int<26, true> v3682 = zpkt3;	// L5809
  v3501.write(v3682);	// L5810
  ac_int<17, true> v3683 = zsys3;	// L5811
  v3502.write(v3683);	// L5812
  ac_int<17, true> v3684 = zsys3;	// L5813
  v3503.write(v3684);	// L5814
  ac_int<17, true> v3685 = zsys3;	// L5815
  v3504.write(v3685);	// L5816
  ac_int<17, true> v3686 = zsys3;	// L5817
  v3505.write(v3686);	// L5818
  int32_t v3687 = zcr3;	// L5819
  v3506.write(v3687);	// L5820
  int32_t v3688 = zcr3;	// L5821
  v3507.write(v3688);	// L5822
  int32_t v3689 = zcr3;	// L5823
  v3508.write(v3689);	// L5824
  int32_t v3690 = zcr3;	// L5825
  v3509.write(v3690);	// L5826
  int32_t v3691 = zcr3;	// L5827
  v3510.write(v3691);	// L5828
  int32_t v3692 = zcr3;	// L5829
  v3511.write(v3692);	// L5830
  int32_t v3693 = zcr3;	// L5831
  v3512.write(v3693);	// L5832
  int32_t v3694 = zcr3;	// L5833
  v3513.write(v3694);	// L5834
  ac_int<26, true> v3695 = oe_r3;	// L5835
  v3498.write(v3695);	// L5836
  ac_int<26, true> v3696 = ow_r3;	// L5837
  v3499.write(v3696);	// L5838
  ac_int<26, true> v3697 = os_r3;	// L5839
  v3500.write(v3697);	// L5840
  ac_int<26, true> v3698 = on_r3;	// L5841
  v3501.write(v3698);	// L5842
  ac_int<17, true> v3699 = txe_r3;	// L5843
  v3502.write(v3699);	// L5844
  ac_int<17, true> v3700 = txw_r3;	// L5845
  v3503.write(v3700);	// L5846
  ac_int<17, true> v3701 = txs_r3;	// L5847
  v3504.write(v3701);	// L5848
  ac_int<17, true> v3702 = txn_r3;	// L5849
  v3505.write(v3702);	// L5850
  int8_t v3703 = cre_r3;	// L5851
  v3506.write(v3703);	// L5852
  int8_t v3704 = crw_r3;	// L5853
  v3507.write(v3704);	// L5854
  int8_t v3705 = crs_r3;	// L5855
  v3508.write(v3705);	// L5856
  int8_t v3706 = crn_r3;	// L5857
  v3509.write(v3706);	// L5858
  int32_t v3707 = sc_r3[0];	// L5859
  v3512.write(v3707);	// L5860
  int32_t v3708 = sc_r3[1];	// L5861
  v3513.write(v3708);	// L5862
  int32_t v3709 = sc_r3[2];	// L5863
  v3510.write(v3709);	// L5864
  int32_t v3710 = sc_r3[3];	// L5865
  v3511.write(v3710);	// L5866
  l_S_t_0_t3: for (int t3 = 0; t3 < 10; t3++) {	// L5867
    ac_int<26, false> v3712 = v3514.read();	// L5868
    ac_int<26, false> p_w3;	// L5869
    p_w3 = v3712;	// L5870
    ac_int<26, false> v3714 = v3515.read();	// L5871
    ac_int<26, false> p_e3;	// L5872
    p_e3 = v3714;	// L5873
    ac_int<26, false> v3716 = v3516.read();	// L5874
    ac_int<26, false> p_n3;	// L5875
    p_n3 = v3716;	// L5876
    ac_int<26, false> v3718 = v3517.read();	// L5877
    ac_int<26, false> p_s3;	// L5878
    p_s3 = v3718;	// L5879
    int32_t v3720 = v3518.read();	// L5880
    uint8_t v3721 = rcred3[0];	// L5881
    ac_int<33, true> v3722 = v3721;	// L5882
    ac_int<33, true> v3723 = v3720;	// L5883
    ac_int<33, true> v3724 = v3722 + v3723;	// L5884
    uint8_t v3725 = v3724;	// L5885
    rcred3[0] = v3725;	// L5886
    int32_t v3726 = v3519.read();	// L5887
    uint8_t v3727 = rcred3[1];	// L5888
    ac_int<33, true> v3728 = v3727;	// L5889
    ac_int<33, true> v3729 = v3726;	// L5890
    ac_int<33, true> v3730 = v3728 + v3729;	// L5891
    uint8_t v3731 = v3730;	// L5892
    rcred3[1] = v3731;	// L5893
    int32_t v3732 = v3520.read();	// L5894
    uint8_t v3733 = rcred3[2];	// L5895
    ac_int<33, true> v3734 = v3733;	// L5896
    ac_int<33, true> v3735 = v3732;	// L5897
    ac_int<33, true> v3736 = v3734 + v3735;	// L5898
    uint8_t v3737 = v3736;	// L5899
    rcred3[2] = v3737;	// L5900
    int32_t v3738 = v3521.read();	// L5901
    uint8_t v3739 = rcred3[3];	// L5902
    ac_int<33, true> v3740 = v3739;	// L5903
    ac_int<33, true> v3741 = v3738;	// L5904
    ac_int<33, true> v3742 = v3740 + v3741;	// L5905
    uint8_t v3743 = v3742;	// L5906
    rcred3[3] = v3743;	// L5907
    int32_t v3744 = v3522.read();	// L5908
    int32_t v3745 = scred3[0];	// L5909
    ac_int<33, true> v3746 = v3745;	// L5910
    ac_int<33, true> v3747 = v3744;	// L5911
    ac_int<33, true> v3748 = v3746 + v3747;	// L5912
    int32_t v3749 = v3748;	// L5913
    scred3[0] = v3749;	// L5914
    int32_t v3750 = v3523.read();	// L5915
    int32_t v3751 = scred3[1];	// L5916
    ac_int<33, true> v3752 = v3751;	// L5917
    ac_int<33, true> v3753 = v3750;	// L5918
    ac_int<33, true> v3754 = v3752 + v3753;	// L5919
    int32_t v3755 = v3754;	// L5920
    scred3[1] = v3755;	// L5921
    int32_t v3756 = v3524.read();	// L5922
    int32_t v3757 = scred3[2];	// L5923
    ac_int<33, true> v3758 = v3757;	// L5924
    ac_int<33, true> v3759 = v3756;	// L5925
    ac_int<33, true> v3760 = v3758 + v3759;	// L5926
    int32_t v3761 = v3760;	// L5927
    scred3[2] = v3761;	// L5928
    int32_t v3762 = v3525.read();	// L5929
    int32_t v3763 = scred3[3];	// L5930
    ac_int<33, true> v3764 = v3763;	// L5931
    ac_int<33, true> v3765 = v3762;	// L5932
    ac_int<33, true> v3766 = v3764 + v3765;	// L5933
    int32_t v3767 = v3766;	// L5934
    scred3[3] = v3767;	// L5935
    ac_int<26, false> fin3[4];	// L5936
    for (int v3769 = 0; v3769 < 4; v3769++) {	// L5937
      fin3[v3769] = 0;	// L5937
    }
    ac_int<26, true> v3770 = p_w3;	// L5938
    fin3[0] = v3770;	// L5939
    ac_int<26, true> v3771 = p_e3;	// L5940
    fin3[1] = v3771;	// L5941
    ac_int<26, true> v3772 = p_n3;	// L5942
    fin3[2] = v3772;	// L5943
    ac_int<26, true> v3773 = p_s3;	// L5944
    fin3[3] = v3773;	// L5945
    l_S_d_0_d15: for (int d15 = 0; d15 < 4; d15++) {	// L5946
      ac_int<26, false> v3775 = fin3[d15];	// L5947
      bool v3776;
      ap_int<26> v3776_tmp = v3775;
      v3776 = v3776_tmp[25];	// L5948
      int32_t v3777 = v3776;	// L5949
      bool v3778 = v3777 == 1;	// L5950
      uint8_t v3779 = rbcnt3[d15];	// L5951
      int32_t v3780 = v3779;	// L5952
      bool v3781 = v3780 < 2;	// L5953
      bool v3782 = v3778 & v3781;	// L5954
      if (v3782) {	// L5955
        ac_int<26, false> v3783 = fin3[d15];	// L5956
        uint8_t v3784 = rbcnt3[d15];	// L5957
        int v3785 = v3784;	// L5958
        rbuf3[d15][v3785] = v3783;	// L5959
        uint8_t v3786 = rbcnt3[d15];	// L5960
        ac_int<33, true> v3787 = v3786;	// L5961
        ac_int<33, true> v3788 = v3787 + 1;	// L5962
        uint8_t v3789 = v3788;	// L5963
        rbcnt3[d15] = v3789;	// L5964
      }
    }
    ac_int<26, false> hd3[4];	// L5967
    for (int v3791 = 0; v3791 < 4; v3791++) {	// L5968
      hd3[v3791] = 0;	// L5968
    }
    int32_t hvld3[4];	// L5969
    for (int v3793 = 0; v3793 < 4; v3793++) {	// L5970
      hvld3[v3793] = 0;	// L5970
    }
    int32_t hit3[4];	// L5971
    for (int v3795 = 0; v3795 < 4; v3795++) {	// L5972
      hit3[v3795] = 0;	// L5972
    }
    int32_t axis3[4];	// L5973
    for (int v3797 = 0; v3797 < 4; v3797++) {	// L5974
      axis3[v3797] = 0;	// L5974
    }
    int32_t v3798 = col_id3;	// L5975
    axis3[0] = v3798;	// L5976
    int32_t v3799 = col_id3;	// L5977
    axis3[1] = v3799;	// L5978
    int32_t v3800 = row_id3;	// L5979
    axis3[2] = v3800;	// L5980
    int32_t v3801 = row_id3;	// L5981
    axis3[3] = v3801;	// L5982
    l_S_d_1_d16: for (int d16 = 0; d16 < 4; d16++) {	// L5983
      uint8_t v3803 = rbcnt3[d16];	// L5984
      int32_t v3804 = v3803;	// L5985
      bool v3805 = v3804 > 0;	// L5986
      if (v3805) {	// L5987
        ac_int<26, false> v3806 = rbuf3[d16][0];	// L5988
        hd3[d16] = v3806;	// L5989
        hvld3[d16] = 1;	// L5990
        ac_int<26, false> v3807 = hd3[d16];	// L5991
        ac_int<4, true> v3808;
        ap_int<26> v3808_tmp = v3807;
        v3808 = v3808_tmp(24, 21);	// L5992
        int32_t v3809 = axis3[d16];	// L5993
        int32_t v3810 = v3808;	// L5994
        bool v3811 = v3810 == v3809;	// L5995
        if (v3811) {	// L5996
          hit3[d16] = 1;	// L5997
        }
      }
    }
    ac_int<26, false> o_crv3;	// L6001
    o_crv3 = 0;	// L6002
    int32_t crv_in3;	// L6003
    crv_in3 = -1;	// L6004
    int32_t v3814 = hit3[3];	// L6005
    bool v3815 = v3814 == 1;	// L6006
    if (v3815) {	// L6007
      ac_int<26, false> v3816 = hd3[3];	// L6008
      o_crv3 = v3816;	// L6009
      crv_in3 = 3;	// L6010
    } else {
      int32_t v3817 = hit3[2];	// L6012
      bool v3818 = v3817 == 1;	// L6013
      if (v3818) {	// L6014
        ac_int<26, false> v3819 = hd3[2];	// L6015
        o_crv3 = v3819;	// L6016
        crv_in3 = 2;	// L6017
      } else {
        int32_t v3820 = hit3[1];	// L6019
        bool v3821 = v3820 == 1;	// L6020
        if (v3821) {	// L6021
          ac_int<26, false> v3822 = hd3[1];	// L6022
          o_crv3 = v3822;	// L6023
          crv_in3 = 1;	// L6024
        } else {
          int32_t v3823 = hit3[0];	// L6026
          bool v3824 = v3823 == 1;	// L6027
          if (v3824) {	// L6028
            ac_int<26, false> v3825 = hd3[0];	// L6029
            o_crv3 = v3825;	// L6030
            crv_in3 = 0;	// L6031
          }
        }
      }
    }
    ac_int<26, false> o_out3[4];	// L6036
    for (int v3827 = 0; v3827 < 4; v3827++) {	// L6037
      o_out3[v3827] = 0;	// L6037
    }
    int32_t pop3[4];	// L6038
    for (int v3829 = 0; v3829 < 4; v3829++) {	// L6039
      pop3[v3829] = 0;	// L6039
    }
    int32_t inj_done3;	// L6040
    inj_done3 = 0;	// L6041
    int32_t idir3;	// L6042
    idir3 = -1;	// L6043
    ac_int<26, true> v3832 = csd_pkt3;	// L6044
    bool v3833;
    ap_int<26> v3833_tmp = v3832;
    v3833 = v3833_tmp[25];	// L6045
    int32_t v3834 = v3833;	// L6046
    bool v3835 = v3834 == 1;	// L6047
    if (v3835) {	// L6048
      int32_t v3836 = csd_dir3;	// L6049
      ac_int<33, true> v3837 = v3836;	// L6050
      ac_int<33, true> v3838 = 3 - v3837;	// L6051
      int32_t v3839 = v3838;	// L6052
      idir3 = v3839;	// L6053
    }
    l_S_o_2_o3: for (int o3 = 0; o3 < 4; o3++) {	// L6055
      uint8_t v3841 = rcred3[o3];	// L6056
      int32_t v3842 = v3841;	// L6057
      bool v3843 = v3842 > 0;	// L6058
      if (v3843) {	// L6059
        int32_t v3844 = idir3;	// L6060
        ac_int<33, true> v3845 = v3844;	// L6061
        ac_int<33, true> v3846 = o3;	// L6062
        bool v3847 = v3845 == v3846;	// L6063
        if (v3847) {	// L6064
          ac_int<26, true> v3848 = csd_pkt3;	// L6065
          o_out3[o3] = v3848;	// L6066
          uint8_t v3849 = rcred3[o3];	// L6067
          ac_int<33, true> v3850 = v3849;	// L6068
          ac_int<33, true> v3851 = v3850 - 1;	// L6069
          uint8_t v3852 = v3851;	// L6070
          rcred3[o3] = v3852;	// L6071
          inj_done3 = 1;	// L6072
        } else {
          int32_t v3853 = hvld3[o3];	// L6074
          bool v3854 = v3853 == 1;	// L6075
          int32_t v3855 = hit3[o3];	// L6076
          bool v3856 = v3855 == 0;	// L6077
          bool v3857 = v3854 & v3856;	// L6078
          if (v3857) {	// L6079
            ac_int<26, false> v3858 = hd3[o3];	// L6080
            o_out3[o3] = v3858;	// L6081
            uint8_t v3859 = rcred3[o3];	// L6082
            ac_int<33, true> v3860 = v3859;	// L6083
            ac_int<33, true> v3861 = v3860 - 1;	// L6084
            uint8_t v3862 = v3861;	// L6085
            rcred3[o3] = v3862;	// L6086
            pop3[o3] = 1;	// L6087
          }
        }
      }
    }
    int32_t v3863 = crv_in3;	// L6092
    bool v3864 = v3863 >= 0;	// L6093
    if (v3864) {	// L6094
      int32_t v3865 = crv_in3;	// L6095
      int v3866 = v3865;	// L6096
      pop3[v3866] = 1;	// L6097
    }
    int32_t ret3[4];	// L6099
    for (int v3868 = 0; v3868 < 4; v3868++) {	// L6100
      ret3[v3868] = 0;	// L6100
    }
    l_S_d_3_d17: for (int d17 = 0; d17 < 4; d17++) {	// L6101
      int32_t v3870 = pop3[d17];	// L6102
      bool v3871 = v3870 == 1;	// L6103
      if (v3871) {	// L6104
        l_S_sft_3_sft3: for (int sft3 = 0; sft3 < 1; sft3++) {	// L6105
          ac_int<26, false> v3873 = rbuf3[d17][(sft3 + 1)];	// L6106
          rbuf3[d17][sft3] = v3873;	// L6107
        }
        uint8_t v3874 = rbcnt3[d17];	// L6109
        ac_int<33, true> v3875 = v3874;	// L6110
        ac_int<33, true> v3876 = v3875 - 1;	// L6111
        uint8_t v3877 = v3876;	// L6112
        rbcnt3[d17] = v3877;	// L6113
        ret3[d17] = 1;	// L6114
      }
    }
    int32_t v3878 = ret3[0];	// L6117
    uint8_t v3879 = v3878;	// L6118
    cre_r3 = v3879;	// L6119
    int32_t v3880 = ret3[1];	// L6120
    uint8_t v3881 = v3880;	// L6121
    crw_r3 = v3881;	// L6122
    int32_t v3882 = ret3[2];	// L6123
    uint8_t v3883 = v3882;	// L6124
    crs_r3 = v3883;	// L6125
    int32_t v3884 = ret3[3];	// L6126
    uint8_t v3885 = v3884;	// L6127
    crn_r3 = v3885;	// L6128
    ac_int<26, false> v3886 = o_out3[0];	// L6129
    oe_r3 = v3886;	// L6130
    ac_int<26, false> v3887 = o_out3[1];	// L6131
    ow_r3 = v3887;	// L6132
    ac_int<26, false> v3888 = o_out3[2];	// L6133
    os_r3 = v3888;	// L6134
    ac_int<26, false> v3889 = o_out3[3];	// L6135
    on_r3 = v3889;	// L6136
    int32_t v3890 = inj_done3;	// L6137
    bool v3891 = v3890 == 1;	// L6138
    if (v3891) {	// L6139
      csd_pkt3 = 0;	// L6140
    }
    ac_int<26, true> v3892 = o_crv3;	// L6142
    bool v3893;
    ap_int<26> v3893_tmp = v3892;
    v3893 = v3893_tmp[25];	// L6143
    int32_t v3894 = v3893;	// L6144
    crv_vld3 = v3894;	// L6145
    ac_int<26, true> v3895 = o_crv3;	// L6146
    int16_t v3896;
    ap_int<26> v3896_tmp = v3895;
    v3896 = v3896_tmp(15, 0);	// L6147
    half v3897;
    union { uint16_t from; half to;} _converter_v3896_to_v3897 = {};
    _converter_v3896_to_v3897.from = v3896;
    v3897 = _converter_v3896_to_v3897.to;	// L6148
    crv_data3 = v3897;	// L6149
    ac_int<26, true> v3898 = o_crv3;	// L6150
    ac_int<4, true> v3899;
    ap_int<26> v3899_tmp = v3898;
    v3899 = v3899_tmp(19, 16);	// L6151
    int32_t v3900 = v3899;	// L6152
    crv_addr3 = v3900;	// L6153
    ac_int<26, true> v3901 = o_crv3;	// L6154
    bool v3902;
    ap_int<26> v3902_tmp = v3901;
    v3902 = v3902_tmp[20];	// L6155
    int32_t v3903 = v3902;	// L6156
    crv_mode3 = v3903;	// L6157
    ac_int<26, true> v3904 = o_crv3;	// L6158
    int16_t v3905;
    ap_int<26> v3905_tmp = v3904;
    v3905 = v3905_tmp(15, 0);	// L6159
    int32_t v3906 = v3905;	// L6160
    crv_raw3 = v3906;	// L6161
    ac_int<17, false> v3907 = v3526.read();	// L6162
    ac_int<17, false> rx_w3;	// L6163
    rx_w3 = v3907;	// L6164
    ac_int<17, false> v3909 = v3527.read();	// L6165
    ac_int<17, false> rx_e3;	// L6166
    rx_e3 = v3909;	// L6167
    ac_int<17, false> v3911 = v3528.read();	// L6168
    ac_int<17, false> rx_n3;	// L6169
    rx_n3 = v3911;	// L6170
    ac_int<17, false> v3913 = v3529.read();	// L6171
    ac_int<17, false> rx_s3;	// L6172
    rx_s3 = v3913;	// L6173
    half rxv3[4];	// L6174
    for (int v3916 = 0; v3916 < 4; v3916++) {	// L6175
      rxv3[v3916] = (double)0.000000;	// L6175
    }
    int32_t rxvld3[4];	// L6176
    for (int v3918 = 0; v3918 < 4; v3918++) {	// L6177
      rxvld3[v3918] = 0;	// L6177
    }
    ac_int<17, true> v3919 = rx_n3;	// L6178
    int16_t v3920;
    ap_int<17> v3920_tmp = v3919;
    v3920 = v3920_tmp(16, 1);	// L6179
    half v3921;
    union { uint16_t from; half to;} _converter_v3920_to_v3921 = {};
    _converter_v3920_to_v3921.from = v3920;
    v3921 = _converter_v3920_to_v3921.to;	// L6180
    rxv3[0] = v3921;	// L6181
    ac_int<17, true> v3922 = rx_n3;	// L6182
    bool v3923;
    ap_int<17> v3923_tmp = v3922;
    v3923 = v3923_tmp[0];	// L6183
    int32_t v3924 = v3923;	// L6184
    rxvld3[0] = v3924;	// L6185
    ac_int<17, true> v3925 = rx_s3;	// L6186
    int16_t v3926;
    ap_int<17> v3926_tmp = v3925;
    v3926 = v3926_tmp(16, 1);	// L6187
    half v3927;
    union { uint16_t from; half to;} _converter_v3926_to_v3927 = {};
    _converter_v3926_to_v3927.from = v3926;
    v3927 = _converter_v3926_to_v3927.to;	// L6188
    rxv3[1] = v3927;	// L6189
    ac_int<17, true> v3928 = rx_s3;	// L6190
    bool v3929;
    ap_int<17> v3929_tmp = v3928;
    v3929 = v3929_tmp[0];	// L6191
    int32_t v3930 = v3929;	// L6192
    rxvld3[1] = v3930;	// L6193
    ac_int<17, true> v3931 = rx_w3;	// L6194
    int16_t v3932;
    ap_int<17> v3932_tmp = v3931;
    v3932 = v3932_tmp(16, 1);	// L6195
    half v3933;
    union { uint16_t from; half to;} _converter_v3932_to_v3933 = {};
    _converter_v3932_to_v3933.from = v3932;
    v3933 = _converter_v3932_to_v3933.to;	// L6196
    rxv3[2] = v3933;	// L6197
    ac_int<17, true> v3934 = rx_w3;	// L6198
    bool v3935;
    ap_int<17> v3935_tmp = v3934;
    v3935 = v3935_tmp[0];	// L6199
    int32_t v3936 = v3935;	// L6200
    rxvld3[2] = v3936;	// L6201
    ac_int<17, true> v3937 = rx_e3;	// L6202
    int16_t v3938;
    ap_int<17> v3938_tmp = v3937;
    v3938 = v3938_tmp(16, 1);	// L6203
    half v3939;
    union { uint16_t from; half to;} _converter_v3938_to_v3939 = {};
    _converter_v3938_to_v3939.from = v3938;
    v3939 = _converter_v3938_to_v3939.to;	// L6204
    rxv3[3] = v3939;	// L6205
    ac_int<17, true> v3940 = rx_e3;	// L6206
    bool v3941;
    ap_int<17> v3941_tmp = v3940;
    v3941 = v3941_tmp[0];	// L6207
    int32_t v3942 = v3941;	// L6208
    rxvld3[3] = v3942;	// L6209
    l_S_d_5_d18: for (int d18 = 0; d18 < 4; d18++) {	// L6210
      int32_t v3944 = rxvld3[d18];	// L6211
      bool v3945 = v3944 == 1;	// L6212
      uint8_t v3946 = hold_cnt3[d18];	// L6213
      int32_t v3947 = v3946;	// L6214
      bool v3948 = v3947 < 2;	// L6215
      bool v3949 = v3945 & v3948;	// L6216
      if (v3949) {	// L6217
        half v3950 = rxv3[d18];	// L6218
        uint8_t v3951 = hold_cnt3[d18];	// L6219
        int v3952 = v3951;	// L6220
        hold_v3[d18][v3952] = v3950;	// L6221
        uint8_t v3953 = hold_cnt3[d18];	// L6222
        ac_int<33, true> v3954 = v3953;	// L6223
        ac_int<33, true> v3955 = v3954 + 1;	// L6224
        uint8_t v3956 = v3955;	// L6225
        hold_cnt3[d18] = v3956;	// L6226
      }
    }
    int32_t retire_ok3;	// L6229
    retire_ok3 = 1;	// L6230
    uint8_t v3958 = sb_v3[0];	// L6231
    int32_t v3959 = v3958;	// L6232
    bool v3960 = v3959 == 1;	// L6233
    uint8_t v3961 = sb_rtr3[0];	// L6234
    int32_t v3962 = v3961;	// L6235
    bool v3963 = v3962 == 0;	// L6236
    uint8_t v3964 = sb_dst3[0];	// L6237
    int32_t v3965 = v3964;	// L6238
    bool v3966 = v3965 >= 12;	// L6239
    bool v3967 = v3960 & v3963;	// L6240
    bool v3968 = v3967 & v3966;	// L6241
    if (v3968) {	// L6242
      uint8_t v3969 = sb_rvld3[0];	// L6243
      int32_t v3970 = v3969;	// L6244
      bool v3971 = v3970 == 1;	// L6245
      uint8_t v3972 = sb_dst3[0];	// L6246
      int32_t v3973 = v3972;	// L6247
      int32_t v3974 = v3973 & 3;	// L6248
      int v3975 = v3974;	// L6249
      int32_t v3976 = txp_v3[v3975];	// L6250
      bool v3977 = v3976 == 1;	// L6251
      bool v3978 = v3971 & v3977;	// L6252
      if (v3978) {	// L6253
        retire_ok3 = 0;	// L6254
      }
    }
    uint8_t v3979 = sb_v3[0];	// L6257
    int32_t v3980 = v3979;	// L6258
    bool v3981 = v3980 == 1;	// L6259
    int32_t v3982 = retire_ok3;	// L6260
    bool v3983 = v3982 == 1;	// L6261
    bool v3984 = v3981 & v3983;	// L6262
    if (v3984) {	// L6263
      uint8_t v3985 = sb_ix3[0];	// L6264
      int v3986 = v3985;	// L6265
      half v3987 = resq3[v3986];	// L6266
      half wb3;	// L6267
      wb3 = v3987;	// L6268
      uint8_t v3989 = sb_cmp3[0];	// L6269
      int32_t v3990 = v3989;	// L6270
      bool v3991 = v3990 == 1;	// L6271
      if (v3991) {	// L6272
        uint8_t v3992 = sb_ix3[0];	// L6273
        int v3993 = v3992;	// L6274
        uint8_t v3994 = cmpq3[v3993];	// L6275
        condition_reg3 = v3994;	// L6276
      }
      uint8_t v3995 = sb_rtr3[0];	// L6278
      int32_t v3996 = v3995;	// L6279
      bool v3997 = v3996 == 1;	// L6280
      if (v3997) {	// L6281
        uint8_t v3998 = sb_inj3[0];	// L6282
        int32_t v3999 = v3998;	// L6283
        bool v4000 = v3999 == 1;	// L6284
        ac_int<26, true> v4001 = csd_pkt3;	// L6285
        bool v4002;
        ap_int<26> v4002_tmp = v4001;
        v4002 = v4002_tmp[25];	// L6286
        int32_t v4003 = v4002;	// L6287
        bool v4004 = v4003 == 0;	// L6288
        bool v4005 = v4000 & v4004;	// L6289
        if (v4005) {	// L6290
          half v4006 = wb3;	// L6291
          uint16_t v4007;
          union { half from; uint16_t to;} _converter_v4006_to_v4007 = {};
          _converter_v4006_to_v4007.from = v4006;
          v4007 = _converter_v4006_to_v4007.to;	// L6292
          ac_int<26, true> v4008 = csd_pkt3;	// L6293
          ac_int<26, true> v4009;
          ap_int<26> v4009_tmp = v4008;
          v4009_tmp(15, 0) = v4007;
          v4009 = v4009_tmp;	// L6294
          csd_pkt3 = v4009;	// L6295
          uint8_t v4010 = sb_dst3[0];	// L6296
          ac_int<4, false> v4011 = v4010;	// L6297
          ac_int<26, true> v4012 = csd_pkt3;	// L6298
          ac_int<26, true> v4013;
          ap_int<26> v4013_tmp = v4012;
          v4013_tmp(19, 16) = v4011;
          v4013 = v4013_tmp;	// L6299
          csd_pkt3 = v4013;	// L6300
          uint8_t v4014 = sb_id3[0];	// L6301
          ac_int<4, false> v4015 = v4014;	// L6302
          ac_int<26, true> v4016 = csd_pkt3;	// L6303
          ac_int<26, true> v4017;
          ap_int<26> v4017_tmp = v4016;
          v4017_tmp(24, 21) = v4015;
          v4017 = v4017_tmp;	// L6304
          csd_pkt3 = v4017;	// L6305
          uint8_t v4018 = sb_rvld3[0];	// L6306
          bool v4019 = v4018;	// L6307
          ac_int<26, true> v4020 = csd_pkt3;	// L6308
          ac_int<26, true> v4021;
          ap_int<26> v4021_tmp = v4020;
          v4021_tmp[25] = v4019;          v4021 = v4021_tmp;	// L6309
          csd_pkt3 = v4021;	// L6310
          uint8_t v4022 = sb_dir3[0];	// L6311
          int32_t v4023 = v4022;	// L6312
          csd_dir3 = v4023;	// L6313
        }
      } else {
        uint8_t v4024 = sb_dst3[0];	// L6316
        int32_t v4025 = v4024;	// L6317
        bool v4026 = v4025 >= 12;	// L6318
        if (v4026) {	// L6319
          uint8_t v4027 = sb_rvld3[0];	// L6320
          int32_t v4028 = v4027;	// L6321
          bool v4029 = v4028 == 1;	// L6322
          if (v4029) {	// L6323
            uint8_t v4030 = sb_dst3[0];	// L6324
            int32_t v4031 = v4030;	// L6325
            int32_t v4032 = v4031 & 3;	// L6326
            int v4033 = v4032;	// L6327
            txp_v3[v4033] = 1;	// L6328
            half v4034 = wb3;	// L6329
            uint8_t v4035 = sb_dst3[0];	// L6330
            int32_t v4036 = v4035;	// L6331
            int32_t v4037 = v4036 & 3;	// L6332
            int v4038 = v4037;	// L6333
            txp_d3[v4038] = v4034;	// L6334
            uint8_t v4039 = sb_dst3[0];	// L6335
            int32_t v4040 = v4039;	// L6336
            int32_t v4041 = v4040 & 3;	// L6337
            int v4042 = v4041;	// L6338
            txp_r3[v4042] = 1;	// L6339
          }
        } else {
          uint8_t v4043 = sb_rvld3[0];	// L6342
          int32_t v4044 = v4043;	// L6343
          bool v4045 = v4044 == 1;	// L6344
          if (v4045) {	// L6345
            uint8_t v4046 = sb_dst3[0];	// L6346
            int32_t v4047 = v4046;	// L6347
            bool v4048 = v4047 < 8;	// L6348
            int32_t v4049 = dsmask3;	// L6349
            int32_t v4050 = v4049 >> v4047;	// L6352
            int32_t v4051 = v4050 & 1;	// L6353
            bool v4052 = v4051 == 1;	// L6354
            bool v4053 = v4048 & v4052;	// L6355
            if (v4053) {	// L6356
              uint8_t v4054 = sb_dst3[0];	// L6357
              int v4055 = v4054;	// L6358
              int32_t v4056 = drf_full3[v4055];	// L6359
              bool v4057 = v4056 == 0;	// L6360
              if (v4057) {	// L6361
                half v4058 = wb3;	// L6362
                uint8_t v4059 = sb_dst3[0];	// L6363
                int v4060 = v4059;	// L6364
                drf3[v4060] = v4058;	// L6365
                uint8_t v4061 = sb_dst3[0];	// L6366
                int v4062 = v4061;	// L6367
                drf_full3[v4062] = 1;	// L6368
              }
            } else {
              half v4063 = wb3;	// L6371
              uint8_t v4064 = sb_dst3[0];	// L6372
              int32_t v4065 = v4064;	// L6373
              int32_t v4066 = v4065 & 7;	// L6374
              int v4067 = v4066;	// L6375
              drf3[v4067] = v4063;	// L6376
            }
          }
        }
      }
    }
    int32_t pc3;	// L6382
    pc3 = -1;	// L6383
    int8_t v4069 = fetch_en3;	// L6384
    int32_t v4070 = v4069;	// L6385
    bool v4071 = v4070 == 1;	// L6386
    if (v4071) {	// L6387
      int8_t v4072 = instr_cnt3;	// L6388
      int32_t v4073 = v4072;	// L6389
      pc3 = v4073;	// L6390
    }
    int32_t instr3;	// L6392
    instr3 = 0;	// L6393
    int32_t v4075 = pc3;	// L6394
    bool v4076 = v4075 >= 0;	// L6395
    if (v4076) {	// L6396
      int32_t v4077 = pc3;	// L6397
      int v4078 = v4077;	// L6398
      int32_t v4079 = irf3[v4078];	// L6399
      instr3 = v4079;	// L6400
    }
    int32_t v4080 = instr3;	// L6402
    int32_t v4081 = v4080 & 15;	// L6403
    int32_t op3;	// L6404
    op3 = v4081;	// L6405
    int32_t v4083 = instr3;	// L6406
    int32_t v4084 = v4083 >> 4;	// L6407
    int32_t v4085 = v4084 & 15;	// L6408
    int32_t dst3;	// L6409
    dst3 = v4085;	// L6410
    int32_t v4087 = instr3;	// L6411
    int32_t v4088 = v4087 >> 8;	// L6412
    int32_t v4089 = v4088 & 15;	// L6413
    int32_t s13;	// L6414
    s13 = v4089;	// L6415
    int32_t v4091 = instr3;	// L6416
    int32_t v4092 = v4091 >> 12;	// L6417
    int32_t v4093 = v4092 & 15;	// L6418
    int32_t s23;	// L6419
    s23 = v4093;	// L6420
    half a3;	// L6421
    a3 = (double)0.000000;	// L6422
    half b3;	// L6423
    b3 = (double)0.000000;	// L6424
    int32_t v4097 = s13;	// L6425
    bool v4098 = v4097 >= 12;	// L6426
    if (v4098) {	// L6427
      int32_t v4099 = s13;	// L6428
      int32_t v4100 = v4099 & 3;	// L6429
      int v4101 = v4100;	// L6430
      half v4102 = hold_v3[v4101][0];	// L6431
      a3 = v4102;	// L6432
    } else {
      int32_t v4103 = s13;	// L6434
      int v4104 = v4103;	// L6435
      half v4105 = drf3[v4104];	// L6436
      a3 = v4105;	// L6437
    }
    int32_t v4106 = s23;	// L6439
    bool v4107 = v4106 >= 12;	// L6440
    if (v4107) {	// L6441
      int32_t v4108 = s23;	// L6442
      int32_t v4109 = v4108 & 3;	// L6443
      int v4110 = v4109;	// L6444
      half v4111 = hold_v3[v4110][0];	// L6445
      b3 = v4111;	// L6446
    } else {
      int32_t v4112 = s23;	// L6448
      int v4113 = v4112;	// L6449
      half v4114 = drf3[v4113];	// L6450
      b3 = v4114;	// L6451
    }
    int32_t a_vld3;	// L6453
    a_vld3 = 1;	// L6454
    int32_t b_vld3;	// L6455
    b_vld3 = 1;	// L6456
    int32_t v4117 = s13;	// L6457
    bool v4118 = v4117 >= 12;	// L6458
    if (v4118) {	// L6459
      a_vld3 = 0;	// L6460
      int32_t v4119 = s13;	// L6461
      int32_t v4120 = v4119 & 3;	// L6462
      int v4121 = v4120;	// L6463
      uint8_t v4122 = hold_cnt3[v4121];	// L6464
      int32_t v4123 = v4122;	// L6465
      bool v4124 = v4123 > 0;	// L6466
      if (v4124) {	// L6467
        a_vld3 = 1;	// L6468
      }
    }
    int32_t v4125 = s23;	// L6471
    bool v4126 = v4125 >= 12;	// L6472
    if (v4126) {	// L6473
      b_vld3 = 0;	// L6474
      int32_t v4127 = s23;	// L6475
      int32_t v4128 = v4127 & 3;	// L6476
      int v4129 = v4128;	// L6477
      uint8_t v4130 = hold_cnt3[v4129];	// L6478
      int32_t v4131 = v4130;	// L6479
      bool v4132 = v4131 > 0;	// L6480
      if (v4132) {	// L6481
        b_vld3 = 1;	// L6482
      }
    }
    int32_t v4133 = s13;	// L6485
    bool v4134 = v4133 < 8;	// L6486
    int32_t v4135 = dsmask3;	// L6487
    int32_t v4136 = v4135 >> v4133;	// L6489
    int32_t v4137 = v4136 & 1;	// L6490
    bool v4138 = v4137 == 1;	// L6491
    bool v4139 = v4134 & v4138;	// L6492
    if (v4139) {	// L6493
      int32_t v4140 = s13;	// L6494
      int v4141 = v4140;	// L6495
      int32_t v4142 = drf_full3[v4141];	// L6496
      bool v4143 = v4142 == 0;	// L6497
      if (v4143) {	// L6498
        a_vld3 = 0;	// L6499
      }
    }
    int32_t v4144 = s23;	// L6502
    bool v4145 = v4144 < 8;	// L6503
    int32_t v4146 = dsmask3;	// L6504
    int32_t v4147 = v4146 >> v4144;	// L6506
    int32_t v4148 = v4147 & 1;	// L6507
    bool v4149 = v4148 == 1;	// L6508
    bool v4150 = v4145 & v4149;	// L6509
    if (v4150) {	// L6510
      int32_t v4151 = s23;	// L6511
      int v4152 = v4151;	// L6512
      int32_t v4153 = drf_full3[v4152];	// L6513
      bool v4154 = v4153 == 0;	// L6514
      if (v4154) {	// L6515
        b_vld3 = 0;	// L6516
      }
    }
    int32_t binop3;	// L6519
    binop3 = 0;	// L6520
    int32_t v4156 = op3;	// L6521
    bool v4157 = v4156 == 0;	// L6522
    bool v4158 = v4156 == 1;	// L6524
    bool v4159 = v4156 == 2;	// L6526
    bool v4160 = v4156 == 8;	// L6528
    bool v4161 = v4156 == 9;	// L6530
    bool v4162 = v4157 | v4158;	// L6531
    bool v4163 = v4162 | v4159;	// L6532
    bool v4164 = v4163 | v4160;	// L6533
    bool v4165 = v4164 | v4161;	// L6534
    if (v4165) {	// L6535
      binop3 = 1;	// L6536
    }
    int32_t raw3;	// L6538
    raw3 = 0;	// L6539
    int32_t cmp_busy3;	// L6540
    cmp_busy3 = 0;	// L6541
    int32_t fwd_a3;	// L6542
    fwd_a3 = 0;	// L6543
    int32_t fwd_a_ix3;	// L6544
    fwd_a_ix3 = 0;	// L6545
    int32_t raw_a3;	// L6546
    raw_a3 = 0;	// L6547
    int32_t fwd_b3;	// L6548
    fwd_b3 = 0;	// L6549
    int32_t fwd_b_ix3;	// L6550
    fwd_b_ix3 = 0;	// L6551
    int32_t raw_b3;	// L6552
    raw_b3 = 0;	// L6553
    l_S_k_6_k6: for (int k6 = 0; k6 < 4; k6++) {	// L6554
      ac_int<34, true> v4175 = k6;	// L6555
      ac_int<34, true> v4176 = v4175 + 1;	// L6556
      int32_t v4177 = v4176;	// L6557
      int32_t kk3;	// L6558
      kk3 = v4177;	// L6559
      int32_t v4179 = kk3;	// L6560
      ac_int<34, true> v4180 = v4179;	// L6561
      ac_int<34, true> v4181 = 4 - v4180;	// L6562
      int32_t v4182 = v4181;	// L6563
      int32_t inflight3;	// L6564
      inflight3 = v4182;	// L6565
      int32_t need3;	// L6566
      need3 = 0;	// L6567
      int32_t v4185 = kk3;	// L6568
      int v4186 = v4185;	// L6569
      uint8_t v4187 = sb_long3[v4186];	// L6570
      int32_t v4188 = v4187;	// L6571
      bool v4189 = v4188 == 1;	// L6572
      if (v4189) {	// L6573
        need3 = 1;	// L6574
      }
      int32_t rdy3;	// L6576
      rdy3 = 0;	// L6577
      int32_t v4191 = inflight3;	// L6578
      int32_t v4192 = need3;	// L6579
      bool v4193 = v4191 >= v4192;	// L6580
      if (v4193) {	// L6581
        rdy3 = 1;	// L6582
      }
      int32_t v4194 = kk3;	// L6584
      int v4195 = v4194;	// L6585
      uint8_t v4196 = sb_v3[v4195];	// L6586
      int32_t v4197 = v4196;	// L6587
      bool v4198 = v4197 == 1;	// L6588
      uint8_t v4199 = sb_rtr3[v4195];	// L6591
      int32_t v4200 = v4199;	// L6592
      bool v4201 = v4200 == 0;	// L6593
      uint8_t v4202 = sb_dst3[v4195];	// L6596
      int32_t v4203 = v4202;	// L6597
      bool v4204 = v4203 < 12;	// L6598
      bool v4205 = v4198 & v4201;	// L6599
      bool v4206 = v4205 & v4204;	// L6600
      if (v4206) {	// L6601
        int32_t v4207 = s13;	// L6602
        bool v4208 = v4207 < 12;	// L6603
        int32_t v4209 = kk3;	// L6604
        int v4210 = v4209;	// L6605
        uint8_t v4211 = sb_dst3[v4210];	// L6606
        int32_t v4212 = v4211;	// L6607
        int32_t v4213 = v4212 & 7;	// L6608
        int32_t v4214 = v4207 & 7;	// L6610
        bool v4215 = v4213 == v4214;	// L6611
        bool v4216 = v4208 & v4215;	// L6612
        if (v4216) {	// L6613
          int32_t v4217 = rdy3;	// L6614
          bool v4218 = v4217 == 1;	// L6615
          if (v4218) {	// L6616
            fwd_a3 = 1;	// L6617
            int32_t v4219 = kk3;	// L6618
            int v4220 = v4219;	// L6619
            uint8_t v4221 = sb_ix3[v4220];	// L6620
            int32_t v4222 = v4221;	// L6621
            fwd_a_ix3 = v4222;	// L6622
            raw_a3 = 0;	// L6623
          } else {
            fwd_a3 = 0;	// L6625
            raw_a3 = 1;	// L6626
          }
        }
        int32_t v4223 = binop3;	// L6629
        bool v4224 = v4223 == 1;	// L6630
        int32_t v4225 = s23;	// L6631
        bool v4226 = v4225 < 12;	// L6632
        int32_t v4227 = kk3;	// L6633
        int v4228 = v4227;	// L6634
        uint8_t v4229 = sb_dst3[v4228];	// L6635
        int32_t v4230 = v4229;	// L6636
        int32_t v4231 = v4230 & 7;	// L6637
        int32_t v4232 = v4225 & 7;	// L6639
        bool v4233 = v4231 == v4232;	// L6640
        bool v4234 = v4224 & v4226;	// L6641
        bool v4235 = v4234 & v4233;	// L6642
        if (v4235) {	// L6643
          int32_t v4236 = rdy3;	// L6644
          bool v4237 = v4236 == 1;	// L6645
          if (v4237) {	// L6646
            fwd_b3 = 1;	// L6647
            int32_t v4238 = kk3;	// L6648
            int v4239 = v4238;	// L6649
            uint8_t v4240 = sb_ix3[v4239];	// L6650
            int32_t v4241 = v4240;	// L6651
            fwd_b_ix3 = v4241;	// L6652
            raw_b3 = 0;	// L6653
          } else {
            fwd_b3 = 0;	// L6655
            raw_b3 = 1;	// L6656
          }
        }
      }
      int32_t v4242 = kk3;	// L6660
      int v4243 = v4242;	// L6661
      uint8_t v4244 = sb_v3[v4243];	// L6662
      int32_t v4245 = v4244;	// L6663
      bool v4246 = v4245 == 1;	// L6664
      uint8_t v4247 = sb_cmp3[v4243];	// L6667
      int32_t v4248 = v4247;	// L6668
      bool v4249 = v4248 == 1;	// L6669
      bool v4250 = v4246 & v4249;	// L6670
      if (v4250) {	// L6671
        cmp_busy3 = 1;	// L6672
      }
    }
    int32_t v4251 = raw_a3;	// L6675
    raw3 = v4251;	// L6676
    int32_t v4252 = binop3;	// L6677
    bool v4253 = v4252 == 1;	// L6678
    int32_t v4254 = raw_b3;	// L6679
    bool v4255 = v4254 == 1;	// L6680
    bool v4256 = v4253 & v4255;	// L6681
    if (v4256) {	// L6682
      raw3 = 1;	// L6683
    }
    int32_t v4257 = fwd_a3;	// L6685
    bool v4258 = v4257 == 1;	// L6686
    if (v4258) {	// L6687
      int32_t v4259 = fwd_a_ix3;	// L6688
      int v4260 = v4259;	// L6689
      half v4261 = resq3[v4260];	// L6690
      a3 = v4261;	// L6691
      a_vld3 = 1;	// L6692
    }
    int32_t v4262 = fwd_b3;	// L6694
    bool v4263 = v4262 == 1;	// L6695
    if (v4263) {	// L6696
      int32_t v4264 = fwd_b_ix3;	// L6697
      int v4265 = v4264;	// L6698
      half v4266 = resq3[v4265];	// L6699
      b3 = v4266;	// L6700
      b_vld3 = 1;	// L6701
    }
    int32_t is_cond3;	// L6703
    is_cond3 = 0;	// L6704
    int32_t v4268 = op3;	// L6705
    bool v4269 = v4268 >= 12;	// L6706
    ac_int<33, true> v4270 = v4268;	// L6708
    bool v4271 = v4270 <= 15;	// L6709
    bool v4272 = v4269 & v4271;	// L6710
    if (v4272) {	// L6711
      is_cond3 = 1;	// L6712
    }
    int32_t grant3;	// L6714
    grant3 = 0;	// L6715
    int32_t v4274 = pc3;	// L6716
    bool v4275 = v4274 >= 0;	// L6717
    if (v4275) {	// L6718
      grant3 = 1;	// L6719
    }
    int32_t v4276 = pc3;	// L6721
    bool v4277 = v4276 >= 0;	// L6722
    int32_t v4278 = a_vld3;	// L6723
    bool v4279 = v4278 == 0;	// L6724
    int32_t v4280 = binop3;	// L6725
    bool v4281 = v4280 == 1;	// L6726
    int32_t v4282 = b_vld3;	// L6727
    bool v4283 = v4282 == 0;	// L6728
    bool v4284 = v4281 & v4283;	// L6729
    bool v4285 = v4279 | v4284;	// L6730
    bool v4286 = v4277 & v4285;	// L6731
    if (v4286) {	// L6732
      grant3 = 0;	// L6733
    }
    int32_t v4287 = pc3;	// L6735
    bool v4288 = v4287 >= 0;	// L6736
    int32_t v4289 = raw3;	// L6737
    bool v4290 = v4289 == 1;	// L6738
    int32_t v4291 = is_cond3;	// L6739
    bool v4292 = v4291 == 1;	// L6740
    int32_t v4293 = cmp_busy3;	// L6741
    bool v4294 = v4293 == 1;	// L6742
    bool v4295 = v4292 & v4294;	// L6743
    bool v4296 = v4290 | v4295;	// L6744
    bool v4297 = v4288 & v4296;	// L6745
    if (v4297) {	// L6746
      grant3 = 0;	// L6747
    }
    int32_t v4298 = retire_ok3;	// L6749
    bool v4299 = v4298 == 0;	// L6750
    if (v4299) {	// L6751
      grant3 = 0;	// L6752
    }
    int32_t v4300 = grant3;	// L6754
    bool v4301 = v4300 == 1;	// L6755
    if (v4301) {	// L6756
      int8_t v4302 = instr_cnt3;	// L6757
      int32_t v4303 = cfg_isz3;	// L6758
      int32_t v4304 = v4302;	// L6759
      bool v4305 = v4304 == v4303;	// L6760
      if (v4305) {	// L6761
        instr_cnt3 = 0;	// L6762
        int8_t v4306 = iter_cnt3;	// L6763
        int32_t v4307 = cfg_itsz3;	// L6764
        ac_int<33, true> v4308 = v4307;	// L6765
        ac_int<33, true> v4309 = v4308 - 1;	// L6766
        ac_int<33, true> v4310 = v4306;	// L6767
        bool v4311 = v4310 == v4309;	// L6768
        if (v4311) {	// L6769
          fetch_en3 = 0;	// L6770
        } else {
          int8_t v4312 = iter_cnt3;	// L6772
          ac_int<33, true> v4313 = v4312;	// L6773
          ac_int<33, true> v4314 = v4313 + 1;	// L6774
          uint8_t v4315 = v4314;	// L6775
          iter_cnt3 = v4315;	// L6776
        }
      } else {
        int8_t v4316 = instr_cnt3;	// L6779
        ac_int<33, true> v4317 = v4316;	// L6780
        ac_int<33, true> v4318 = v4317 + 1;	// L6781
        uint8_t v4319 = v4318;	// L6782
        instr_cnt3 = v4319;	// L6783
      }
    }
    int32_t c13;	// L6786
    c13 = -1;	// L6787
    int32_t c23;	// L6788
    c23 = -1;	// L6789
    int32_t v4322 = grant3;	// L6790
    bool v4323 = v4322 == 1;	// L6791
    int32_t v4324 = s13;	// L6792
    bool v4325 = v4324 >= 12;	// L6793
    bool v4326 = v4323 & v4325;	// L6794
    if (v4326) {	// L6795
      int32_t v4327 = s13;	// L6796
      int32_t v4328 = v4327 & 3;	// L6797
      c13 = v4328;	// L6798
    }
    int32_t v4329 = grant3;	// L6800
    bool v4330 = v4329 == 1;	// L6801
    int32_t v4331 = s23;	// L6802
    bool v4332 = v4331 >= 12;	// L6803
    bool v4333 = v4330 & v4332;	// L6804
    if (v4333) {	// L6805
      int32_t v4334 = s23;	// L6806
      int32_t v4335 = v4334 & 3;	// L6807
      c23 = v4335;	// L6808
    }
    int32_t v4336 = c13;	// L6810
    bool v4337 = v4336 >= 0;	// L6811
    if (v4337) {	// L6812
      int32_t v4338 = c13;	// L6813
      int v4339 = v4338;	// L6814
      half v4340 = hold_v3[v4339][1];	// L6815
      hold_v3[v4339][0] = v4340;	// L6818
      int32_t v4341 = c13;	// L6819
      int v4342 = v4341;	// L6820
      uint8_t v4343 = hold_cnt3[v4342];	// L6821
      ac_int<33, true> v4344 = v4343;	// L6822
      ac_int<33, true> v4345 = v4344 - 1;	// L6823
      uint8_t v4346 = v4345;	// L6824
      hold_cnt3[v4342] = v4346;	// L6827
    }
    int32_t v4347 = c23;	// L6829
    bool v4348 = v4347 >= 0;	// L6830
    int32_t v4349 = c13;	// L6832
    bool v4350 = v4347 != v4349;	// L6833
    bool v4351 = v4348 & v4350;	// L6834
    if (v4351) {	// L6835
      int32_t v4352 = c23;	// L6836
      int v4353 = v4352;	// L6837
      half v4354 = hold_v3[v4353][1];	// L6838
      hold_v3[v4353][0] = v4354;	// L6841
      int32_t v4355 = c23;	// L6842
      int v4356 = v4355;	// L6843
      uint8_t v4357 = hold_cnt3[v4356];	// L6844
      ac_int<33, true> v4358 = v4357;	// L6845
      ac_int<33, true> v4359 = v4358 - 1;	// L6846
      uint8_t v4360 = v4359;	// L6847
      hold_cnt3[v4356] = v4360;	// L6850
    }
    l_S_d_7_d19: for (int d19 = 0; d19 < 4; d19++) {	// L6852
      sc_r3[d19] = 0;	// L6853
    }
    int32_t v4362 = c13;	// L6855
    bool v4363 = v4362 >= 0;	// L6856
    if (v4363) {	// L6857
      int32_t v4364 = c13;	// L6858
      int v4365 = v4364;	// L6859
      sc_r3[v4365] = 1;	// L6860
    }
    int32_t v4366 = c23;	// L6862
    bool v4367 = v4366 >= 0;	// L6863
    int32_t v4368 = c13;	// L6865
    bool v4369 = v4366 != v4368;	// L6866
    bool v4370 = v4367 & v4369;	// L6867
    if (v4370) {	// L6868
      int32_t v4371 = c23;	// L6869
      int v4372 = v4371;	// L6870
      sc_r3[v4372] = 1;	// L6871
    }
    int32_t v4373 = grant3;	// L6873
    bool v4374 = v4373 == 1;	// L6874
    int32_t v4375 = s13;	// L6875
    bool v4376 = v4375 < 8;	// L6876
    int32_t v4377 = dsmask3;	// L6877
    int32_t v4378 = v4377 >> v4375;	// L6879
    int32_t v4379 = v4378 & 1;	// L6880
    bool v4380 = v4379 == 1;	// L6881
    bool v4381 = v4374 & v4376;	// L6882
    bool v4382 = v4381 & v4380;	// L6883
    if (v4382) {	// L6884
      int32_t v4383 = s13;	// L6885
      int v4384 = v4383;	// L6886
      drf_full3[v4384] = 0;	// L6887
    }
    int32_t v4385 = grant3;	// L6889
    bool v4386 = v4385 == 1;	// L6890
    int32_t v4387 = s23;	// L6891
    bool v4388 = v4387 < 8;	// L6892
    int32_t v4389 = dsmask3;	// L6893
    int32_t v4390 = v4389 >> v4387;	// L6895
    int32_t v4391 = v4390 & 1;	// L6896
    bool v4392 = v4391 == 1;	// L6897
    bool v4393 = v4386 & v4388;	// L6898
    bool v4394 = v4393 & v4392;	// L6899
    if (v4394) {	// L6900
      int32_t v4395 = s23;	// L6901
      int v4396 = v4395;	// L6902
      drf_full3[v4396] = 0;	// L6903
    }
    half res3;	// L6905
    res3 = (double)0.000000;	// L6906
    int32_t v4398 = op3;	// L6907
    bool v4399 = v4398 == 0;	// L6908
    if (v4399) {	// L6909
      half v4400 = a3;	// L6910
      half v4401 = b3;	// L6911
      half v4402 = v4400 + v4401;	// L6912
      res3 = v4402;	// L6913
    } else {
      int32_t v4403 = op3;	// L6915
      bool v4404 = v4403 == 1;	// L6916
      if (v4404) {	// L6917
        half v4405 = a3;	// L6918
        half v4406 = b3;	// L6919
        half v4407 = v4405 - v4406;	// L6920
        res3 = v4407;	// L6921
      } else {
        int32_t v4408 = op3;	// L6923
        bool v4409 = v4408 == 2;	// L6924
        if (v4409) {	// L6925
          half v4410 = a3;	// L6926
          half v4411 = b3;	// L6927
          half v4412 = v4410 * v4411;	// L6928
          res3 = v4412;	// L6929
        } else {
          int32_t v4413 = op3;	// L6931
          bool v4414 = v4413 == 8;	// L6932
          if (v4414) {	// L6933
            half v4415 = a3;	// L6934
            half v4416 = b3;	// L6935
            bool v4417 = v4415 >= v4416;	// L6936
            if (v4417) {	// L6937
              res3 = (double)1.000000;	// L6938
            } else {
              res3 = (double)-1.000000;	// L6940
            }
          } else {
            int32_t v4418 = op3;	// L6943
            bool v4419 = v4418 == 9;	// L6944
            if (v4419) {	// L6945
              half v4420 = a3;	// L6946
              half v4421 = b3;	// L6947
              bool v4422 = v4420 < v4421;	// L6948
              if (v4422) {	// L6949
                res3 = (double)1.000000;	// L6950
              } else {
                res3 = (double)-1.000000;	// L6952
              }
            } else {
              half v4423 = a3;	// L6955
              res3 = v4423;	// L6956
            }
          }
        }
      }
    }
    int32_t v4424 = a_vld3;	// L6962
    int32_t res_vld3;	// L6963
    res_vld3 = v4424;	// L6964
    int32_t v4426 = op3;	// L6965
    bool v4427 = v4426 == 0;	// L6966
    bool v4428 = v4426 == 1;	// L6968
    bool v4429 = v4426 == 2;	// L6970
    bool v4430 = v4426 == 8;	// L6972
    bool v4431 = v4426 == 9;	// L6974
    bool v4432 = v4427 | v4428;	// L6975
    bool v4433 = v4432 | v4429;	// L6976
    bool v4434 = v4433 | v4430;	// L6977
    bool v4435 = v4434 | v4431;	// L6978
    if (v4435) {	// L6979
      int32_t v4436 = a_vld3;	// L6980
      int32_t v4437 = b_vld3;	// L6981
      int64_t v4438 = v4436;	// L6982
      int64_t v4439 = v4437;	// L6983
      int64_t v4440 = v4438 * v4439;	// L6984
      int32_t v4441 = v4440;	// L6985
      res_vld3 = v4441;	// L6986
    }
    int32_t v4442 = grant3;	// L6988
    bool v4443 = v4442 == 0;	// L6989
    if (v4443) {	// L6990
      res_vld3 = 0;	// L6991
    }
    int32_t is_rtr3;	// L6993
    is_rtr3 = 0;	// L6994
    int32_t v4445 = op3;	// L6995
    bool v4446 = v4445 >= 4;	// L6996
    ac_int<33, true> v4447 = v4445;	// L6998
    bool v4448 = v4447 <= 7;	// L6999
    bool v4449 = v4446 & v4448;	// L7000
    if (v4449) {	// L7001
      is_rtr3 = 1;	// L7002
    }
    int32_t v4450 = retire_ok3;	// L7004
    bool v4451 = v4450 == 1;	// L7005
    if (v4451) {	// L7006
      l_S_k_8_k7: for (int k7 = 0; k7 < 4; k7++) {	// L7007
        uint8_t v4453 = sb_v3[(k7 + 1)];	// L7008
        sb_v3[k7] = v4453;	// L7009
        uint8_t v4454 = sb_dst3[(k7 + 1)];	// L7010
        sb_dst3[k7] = v4454;	// L7011
        uint8_t v4455 = sb_cmp3[(k7 + 1)];	// L7012
        sb_cmp3[k7] = v4455;	// L7013
        uint8_t v4456 = sb_rtr3[(k7 + 1)];	// L7014
        sb_rtr3[k7] = v4456;	// L7015
        uint8_t v4457 = sb_inj3[(k7 + 1)];	// L7016
        sb_inj3[k7] = v4457;	// L7017
        uint8_t v4458 = sb_dir3[(k7 + 1)];	// L7018
        sb_dir3[k7] = v4458;	// L7019
        uint8_t v4459 = sb_id3[(k7 + 1)];	// L7020
        sb_id3[k7] = v4459;	// L7021
        uint8_t v4460 = sb_rvld3[(k7 + 1)];	// L7022
        sb_rvld3[k7] = v4460;	// L7023
        uint8_t v4461 = sb_ix3[(k7 + 1)];	// L7024
        sb_ix3[k7] = v4461;	// L7025
        uint8_t v4462 = sb_long3[(k7 + 1)];	// L7026
        sb_long3[k7] = v4462;	// L7027
      }
      sb_v3[4] = 0;	// L7029
    }
    int32_t v4463 = grant3;	// L7031
    bool v4464 = v4463 == 1;	// L7032
    if (v4464) {	// L7033
      half v4465 = res3;	// L7034
      int8_t v4466 = resq_wr3;	// L7035
      int v4467 = v4466;	// L7036
      resq3[v4467] = v4465;	// L7037
      int32_t cq3;	// L7038
      cq3 = 0;	// L7039
      int32_t v4469 = op3;	// L7040
      bool v4470 = v4469 == 8;	// L7041
      if (v4470) {	// L7042
        half v4471 = a3;	// L7043
        half v4472 = b3;	// L7044
        bool v4473 = v4471 >= v4472;	// L7045
        if (v4473) {	// L7046
          cq3 = 1;	// L7047
        }
      }
      int32_t v4474 = op3;	// L7050
      bool v4475 = v4474 == 9;	// L7051
      if (v4475) {	// L7052
        half v4476 = a3;	// L7053
        half v4477 = b3;	// L7054
        bool v4478 = v4476 < v4477;	// L7055
        if (v4478) {	// L7056
          cq3 = 1;	// L7057
        }
      }
      int32_t v4479 = cq3;	// L7060
      uint8_t v4480 = v4479;	// L7061
      int8_t v4481 = resq_wr3;	// L7062
      int v4482 = v4481;	// L7063
      cmpq3[v4482] = v4480;	// L7064
      sb_v3[4] = 1;	// L7065
      int32_t v4483 = dst3;	// L7066
      uint8_t v4484 = v4483;	// L7067
      sb_dst3[4] = v4484;	// L7068
      int8_t v4485 = resq_wr3;	// L7069
      sb_ix3[4] = v4485;	// L7070
      int32_t v4486 = binop3;	// L7071
      uint8_t v4487 = v4486;	// L7072
      sb_long3[4] = v4487;	// L7073
      sb_cmp3[4] = 0;	// L7074
      int32_t v4488 = op3;	// L7075
      bool v4489 = v4488 == 8;	// L7076
      bool v4490 = v4488 == 9;	// L7078
      bool v4491 = v4489 | v4490;	// L7079
      if (v4491) {	// L7080
        sb_cmp3[4] = 1;	// L7081
      }
      int32_t v4492 = is_rtr3;	// L7083
      int32_t rtrf3;	// L7084
      rtrf3 = v4492;	// L7085
      int32_t v4494 = is_cond3;	// L7086
      bool v4495 = v4494 == 1;	// L7087
      if (v4495) {	// L7088
        rtrf3 = 1;	// L7089
      }
      int32_t v4496 = rtrf3;	// L7091
      uint8_t v4497 = v4496;	// L7092
      sb_rtr3[4] = v4497;	// L7093
      int32_t v4498 = is_rtr3;	// L7094
      int32_t inj3;	// L7095
      inj3 = v4498;	// L7096
      int32_t v4500 = is_cond3;	// L7097
      bool v4501 = v4500 == 1;	// L7098
      int8_t v4502 = condition_reg3;	// L7099
      int32_t v4503 = v4502;	// L7100
      bool v4504 = v4503 == 1;	// L7101
      bool v4505 = v4501 & v4504;	// L7102
      if (v4505) {	// L7103
        inj3 = 1;	// L7104
      }
      int32_t v4506 = inj3;	// L7106
      uint8_t v4507 = v4506;	// L7107
      sb_inj3[4] = v4507;	// L7108
      int32_t v4508 = op3;	// L7109
      int32_t v4509 = v4508 & 3;	// L7110
      uint8_t v4510 = v4509;	// L7111
      sb_dir3[4] = v4510;	// L7112
      int32_t v4511 = s23;	// L7113
      uint8_t v4512 = v4511;	// L7114
      sb_id3[4] = v4512;	// L7115
      int32_t v4513 = res_vld3;	// L7116
      uint8_t v4514 = v4513;	// L7117
      sb_rvld3[4] = v4514;	// L7118
      int8_t v4515 = resq_wr3;	// L7119
      ac_int<33, true> v4516 = v4515;	// L7120
      ac_int<33, true> v4517 = v4516 + 1;	// L7121
      ac_int<33, true> v4518 = v4517 & 7;	// L7122
      uint8_t v4519 = v4518;	// L7123
      resq_wr3 = v4519;	// L7124
    }
    txn_r3 = 0;	// L7126
    txs_r3 = 0;	// L7127
    txw_r3 = 0;	// L7128
    txe_r3 = 0;	// L7129
    int32_t v4520 = txp_v3[0];	// L7130
    bool v4521 = v4520 == 1;	// L7131
    int32_t v4522 = scred3[0];	// L7132
    bool v4523 = v4522 > 0;	// L7133
    bool v4524 = v4521 & v4523;	// L7134
    if (v4524) {	// L7135
      ac_int<17, false> twn3;	// L7136
      twn3 = 0;	// L7137
      ac_int<17, true> v4526 = twn3;	// L7138
      ac_int<17, true> v4527;
      ap_int<17> v4527_tmp = v4526;
      v4527_tmp[0] = 1;      v4527 = v4527_tmp;	// L7139
      twn3 = v4527;	// L7140
      half v4528 = txp_d3[0];	// L7141
      uint16_t v4529;
      union { half from; uint16_t to;} _converter_v4528_to_v4529 = {};
      _converter_v4528_to_v4529.from = v4528;
      v4529 = _converter_v4528_to_v4529.to;	// L7142
      ac_int<17, true> v4530 = twn3;	// L7143
      ac_int<17, true> v4531;
      ap_int<17> v4531_tmp = v4530;
      v4531_tmp(16, 1) = v4529;
      v4531 = v4531_tmp;	// L7144
      twn3 = v4531;	// L7145
      ac_int<17, true> v4532 = twn3;	// L7146
      txn_r3 = v4532;	// L7147
      txp_v3[0] = 0;	// L7148
      int32_t v4533 = scred3[0];	// L7149
      ac_int<33, true> v4534 = v4533;	// L7150
      ac_int<33, true> v4535 = v4534 - 1;	// L7151
      int32_t v4536 = v4535;	// L7152
      scred3[0] = v4536;	// L7153
    }
    int32_t v4537 = txp_v3[1];	// L7155
    bool v4538 = v4537 == 1;	// L7156
    int32_t v4539 = scred3[1];	// L7157
    bool v4540 = v4539 > 0;	// L7158
    bool v4541 = v4538 & v4540;	// L7159
    if (v4541) {	// L7160
      ac_int<17, false> tws3;	// L7161
      tws3 = 0;	// L7162
      ac_int<17, true> v4543 = tws3;	// L7163
      ac_int<17, true> v4544;
      ap_int<17> v4544_tmp = v4543;
      v4544_tmp[0] = 1;      v4544 = v4544_tmp;	// L7164
      tws3 = v4544;	// L7165
      half v4545 = txp_d3[1];	// L7166
      uint16_t v4546;
      union { half from; uint16_t to;} _converter_v4545_to_v4546 = {};
      _converter_v4545_to_v4546.from = v4545;
      v4546 = _converter_v4545_to_v4546.to;	// L7167
      ac_int<17, true> v4547 = tws3;	// L7168
      ac_int<17, true> v4548;
      ap_int<17> v4548_tmp = v4547;
      v4548_tmp(16, 1) = v4546;
      v4548 = v4548_tmp;	// L7169
      tws3 = v4548;	// L7170
      ac_int<17, true> v4549 = tws3;	// L7171
      txs_r3 = v4549;	// L7172
      txp_v3[1] = 0;	// L7173
      int32_t v4550 = scred3[1];	// L7174
      ac_int<33, true> v4551 = v4550;	// L7175
      ac_int<33, true> v4552 = v4551 - 1;	// L7176
      int32_t v4553 = v4552;	// L7177
      scred3[1] = v4553;	// L7178
    }
    int32_t v4554 = txp_v3[2];	// L7180
    bool v4555 = v4554 == 1;	// L7181
    int32_t v4556 = scred3[2];	// L7182
    bool v4557 = v4556 > 0;	// L7183
    bool v4558 = v4555 & v4557;	// L7184
    if (v4558) {	// L7185
      ac_int<17, false> tww3;	// L7186
      tww3 = 0;	// L7187
      ac_int<17, true> v4560 = tww3;	// L7188
      ac_int<17, true> v4561;
      ap_int<17> v4561_tmp = v4560;
      v4561_tmp[0] = 1;      v4561 = v4561_tmp;	// L7189
      tww3 = v4561;	// L7190
      half v4562 = txp_d3[2];	// L7191
      uint16_t v4563;
      union { half from; uint16_t to;} _converter_v4562_to_v4563 = {};
      _converter_v4562_to_v4563.from = v4562;
      v4563 = _converter_v4562_to_v4563.to;	// L7192
      ac_int<17, true> v4564 = tww3;	// L7193
      ac_int<17, true> v4565;
      ap_int<17> v4565_tmp = v4564;
      v4565_tmp(16, 1) = v4563;
      v4565 = v4565_tmp;	// L7194
      tww3 = v4565;	// L7195
      ac_int<17, true> v4566 = tww3;	// L7196
      txw_r3 = v4566;	// L7197
      txp_v3[2] = 0;	// L7198
      int32_t v4567 = scred3[2];	// L7199
      ac_int<33, true> v4568 = v4567;	// L7200
      ac_int<33, true> v4569 = v4568 - 1;	// L7201
      int32_t v4570 = v4569;	// L7202
      scred3[2] = v4570;	// L7203
    }
    int32_t v4571 = txp_v3[3];	// L7205
    bool v4572 = v4571 == 1;	// L7206
    int32_t v4573 = scred3[3];	// L7207
    bool v4574 = v4573 > 0;	// L7208
    bool v4575 = v4572 & v4574;	// L7209
    if (v4575) {	// L7210
      ac_int<17, false> twe3;	// L7211
      twe3 = 0;	// L7212
      ac_int<17, true> v4577 = twe3;	// L7213
      ac_int<17, true> v4578;
      ap_int<17> v4578_tmp = v4577;
      v4578_tmp[0] = 1;      v4578 = v4578_tmp;	// L7214
      twe3 = v4578;	// L7215
      half v4579 = txp_d3[3];	// L7216
      uint16_t v4580;
      union { half from; uint16_t to;} _converter_v4579_to_v4580 = {};
      _converter_v4579_to_v4580.from = v4579;
      v4580 = _converter_v4579_to_v4580.to;	// L7217
      ac_int<17, true> v4581 = twe3;	// L7218
      ac_int<17, true> v4582;
      ap_int<17> v4582_tmp = v4581;
      v4582_tmp(16, 1) = v4580;
      v4582 = v4582_tmp;	// L7219
      twe3 = v4582;	// L7220
      ac_int<17, true> v4583 = twe3;	// L7221
      txe_r3 = v4583;	// L7222
      txp_v3[3] = 0;	// L7223
      int32_t v4584 = scred3[3];	// L7224
      ac_int<33, true> v4585 = v4584;	// L7225
      ac_int<33, true> v4586 = v4585 - 1;	// L7226
      int32_t v4587 = v4586;	// L7227
      scred3[3] = v4587;	// L7228
    }
    int32_t v4588 = crv_vld3;	// L7230
    bool v4589 = v4588 == 1;	// L7231
    if (v4589) {	// L7232
      int32_t v4590 = crv_mode3;	// L7233
      bool v4591 = v4590 == 1;	// L7234
      if (v4591) {	// L7235
        int32_t v4592 = crv_addr3;	// L7236
        int32_t v4593 = v4592 >> 3;	// L7237
        int32_t v4594 = v4593 & 1;	// L7238
        bool v4595 = v4594 == 1;	// L7239
        if (v4595) {	// L7240
          int32_t v4596 = crv_raw3;	// L7241
          int32_t v4597 = crv_addr3;	// L7242
          int32_t v4598 = v4597 & 7;	// L7243
          int v4599 = v4598;	// L7244
          irf3[v4599] = v4596;	// L7245
        } else {
          int32_t v4600 = crv_addr3;	// L7247
          bool v4601 = v4600 == 0;	// L7248
          if (v4601) {	// L7249
            int32_t v4602 = crv_raw3;	// L7250
            int32_t v4603 = v4602 & 255;	// L7251
            dsmask3 = v4603;	// L7252
            int32_t v4604 = crv_raw3;	// L7253
            int32_t v4605 = v4604 >> 8;	// L7254
            int32_t v4606 = v4605 & 7;	// L7255
            cfg_isz3 = v4606;	// L7256
            int32_t v4607 = crv_raw3;	// L7257
            int32_t v4608 = v4607 >> 15;	// L7258
            int32_t v4609 = v4608 & 1;	// L7259
            bool v4610 = v4609 == 1;	// L7260
            if (v4610) {	// L7261
              fetch_en3 = 1;	// L7262
              instr_cnt3 = 0;	// L7263
              iter_cnt3 = 0;	// L7264
            }
          } else {
            int32_t v4611 = crv_addr3;	// L7267
            bool v4612 = v4611 == 1;	// L7268
            if (v4612) {	// L7269
              int32_t v4613 = crv_raw3;	// L7270
              int32_t v4614 = v4613 & 255;	// L7271
              cfg_itsz3 = v4614;	// L7272
            }
          }
        }
      } else {
        int32_t v4615 = crv_addr3;	// L7277
        int32_t v4616 = v4615 >> 2;	// L7278
        int32_t v4617 = v4616 & 3;	// L7279
        bool v4618 = v4617 == 3;	// L7280
        if (v4618) {	// L7281
          int32_t v4619 = crv_addr3;	// L7282
          int32_t v4620 = v4619 & 3;	// L7283
          int v4621 = v4620;	// L7284
          txp_v3[v4621] = 1;	// L7285
          half v4622 = crv_data3;	// L7286
          int32_t v4623 = crv_addr3;	// L7287
          int32_t v4624 = v4623 & 3;	// L7288
          int v4625 = v4624;	// L7289
          txp_d3[v4625] = v4622;	// L7290
          int32_t v4626 = crv_addr3;	// L7291
          int32_t v4627 = v4626 & 3;	// L7292
          int v4628 = v4627;	// L7293
          txp_r3[v4628] = 1;	// L7294
        } else {
          int32_t v4629 = crv_addr3;	// L7296
          bool v4630 = v4629 < 8;	// L7297
          int32_t v4631 = dsmask3;	// L7298
          int32_t v4632 = v4631 >> v4629;	// L7300
          int32_t v4633 = v4632 & 1;	// L7301
          bool v4634 = v4633 == 1;	// L7302
          bool v4635 = v4630 & v4634;	// L7303
          if (v4635) {	// L7304
            int32_t v4636 = crv_addr3;	// L7305
            int v4637 = v4636;	// L7306
            int32_t v4638 = drf_full3[v4637];	// L7307
            bool v4639 = v4638 == 0;	// L7308
            if (v4639) {	// L7309
              half v4640 = crv_data3;	// L7310
              int32_t v4641 = crv_addr3;	// L7311
              int v4642 = v4641;	// L7312
              drf3[v4642] = v4640;	// L7313
              int32_t v4643 = crv_addr3;	// L7314
              int v4644 = v4643;	// L7315
              drf_full3[v4644] = 1;	// L7316
            }
          } else {
            half v4645 = crv_data3;	// L7319
            int32_t v4646 = crv_addr3;	// L7320
            int v4647 = v4646;	// L7321
            drf3[v4647] = v4645;	// L7322
          }
        }
      }
    }
    ac_int<26, true> v4648 = oe_r3;	// L7327
    v3498.write(v4648);	// L7328
    ac_int<26, true> v4649 = ow_r3;	// L7329
    v3499.write(v4649);	// L7330
    ac_int<26, true> v4650 = os_r3;	// L7331
    v3500.write(v4650);	// L7332
    ac_int<26, true> v4651 = on_r3;	// L7333
    v3501.write(v4651);	// L7334
    ac_int<17, true> v4652 = txe_r3;	// L7335
    v3502.write(v4652);	// L7336
    ac_int<17, true> v4653 = txw_r3;	// L7337
    v3503.write(v4653);	// L7338
    ac_int<17, true> v4654 = txs_r3;	// L7339
    v3504.write(v4654);	// L7340
    ac_int<17, true> v4655 = txn_r3;	// L7341
    v3505.write(v4655);	// L7342
    int8_t v4656 = cre_r3;	// L7343
    v3506.write(v4656);	// L7344
    int8_t v4657 = crw_r3;	// L7345
    v3507.write(v4657);	// L7346
    int8_t v4658 = crs_r3;	// L7347
    v3508.write(v4658);	// L7348
    int8_t v4659 = crn_r3;	// L7349
    v3509.write(v4659);	// L7350
    int32_t v4660 = sc_r3[0];	// L7351
    v3512.write(v4660);	// L7352
    int32_t v4661 = sc_r3[1];	// L7353
    v3513.write(v4661);	// L7354
    int32_t v4662 = sc_r3[2];	// L7355
    v3510.write(v4662);	// L7356
    int32_t v4663 = sc_r3[3];	// L7357
    v3511.write(v4663);	// L7358
  }
}

void drv_w_0(
  half v4664[2][10],
  int32_t v4665[2][10],
  ac_channel< ac_int<17, false> >& v4666,
  ac_channel< ac_int<17, false> >& v4667,
  ac_channel< int32_t >& v4668,
  ac_channel< int32_t >& v4669
) {	// L7362
  int32_t dcred[2];	// L7371
  for (int v4671 = 0; v4671 < 2; v4671++) {	// L7372
    dcred[v4671] = 0;	// L7372
  }
  int32_t sp[2];	// L7373
  for (int v4673 = 0; v4673 < 2; v4673++) {	// L7374
    sp[v4673] = 0;	// L7374
  }
  ac_int<17, false> zw;	// L7375
  zw = 0;	// L7376
  ac_int<17, true> v4675 = zw;	// L7377
  v4666.write(v4675);	// L7378
  ac_int<17, true> v4676 = zw;	// L7379
  v4667.write(v4676);	// L7380
  ac_int<17, true> v4677 = zw;	// L7381
  v4666.write(v4677);	// L7382
  ac_int<17, true> v4678 = zw;	// L7383
  v4667.write(v4678);	// L7384
  ac_int<17, true> v4679 = zw;	// L7385
  v4666.write(v4679);	// L7386
  ac_int<17, true> v4680 = zw;	// L7387
  v4667.write(v4680);	// L7388
  ac_int<17, true> v4681 = zw;	// L7389
  v4666.write(v4681);	// L7390
  ac_int<17, true> v4682 = zw;	// L7391
  v4667.write(v4682);	// L7392
  ac_int<17, true> v4683 = zw;	// L7393
  v4666.write(v4683);	// L7394
  ac_int<17, true> v4684 = zw;	// L7395
  v4667.write(v4684);	// L7396
  l_S_t_0_t4: for (int t4 = 0; t4 < 10; t4++) {	// L7397
    int32_t v4686 = v4668.read();	// L7398
    int32_t v4687 = dcred[0];	// L7399
    ac_int<33, true> v4688 = v4687;	// L7400
    ac_int<33, true> v4689 = v4686;	// L7401
    ac_int<33, true> v4690 = v4688 + v4689;	// L7402
    int32_t v4691 = v4690;	// L7403
    dcred[0] = v4691;	// L7404
    ac_int<17, false> w;	// L7405
    w = 0;	// L7406
    int32_t v4693 = sp[0];	// L7407
    bool v4694 = v4693 < 10;	// L7408
    ac_int<33, true> v4695 = t4;	// L7410
    ac_int<33, true> v4696 = v4693;	// L7411
    bool v4697 = v4695 >= v4696;	// L7412
    bool v4698 = v4694 & v4697;	// L7413
    if (v4698) {	// L7414
      int32_t v4699 = sp[0];	// L7415
      int v4700 = v4699;	// L7416
      int32_t v4701 = v4665[0][v4700];	// L7417
      bool v4702 = v4701 == 0;	// L7418
      if (v4702) {	// L7419
        int32_t v4703 = sp[0];	// L7420
        ac_int<33, true> v4704 = v4703;	// L7421
        ac_int<33, true> v4705 = v4704 + 1;	// L7422
        int32_t v4706 = v4705;	// L7423
        sp[0] = v4706;	// L7424
      } else {
        int32_t v4707 = dcred[0];	// L7426
        bool v4708 = v4707 > 0;	// L7427
        if (v4708) {	// L7428
          ac_int<17, true> v4709 = w;	// L7429
          ac_int<17, true> v4710;
          ap_int<17> v4710_tmp = v4709;
          v4710_tmp[0] = 1;          v4710 = v4710_tmp;	// L7430
          w = v4710;	// L7431
          int32_t v4711 = sp[0];	// L7432
          int v4712 = v4711;	// L7433
          half v4713 = v4664[0][v4712];	// L7434
          uint16_t v4714;
          union { half from; uint16_t to;} _converter_v4713_to_v4714 = {};
          _converter_v4713_to_v4714.from = v4713;
          v4714 = _converter_v4713_to_v4714.to;	// L7435
          ac_int<17, true> v4715 = w;	// L7436
          ac_int<17, true> v4716;
          ap_int<17> v4716_tmp = v4715;
          v4716_tmp(16, 1) = v4714;
          v4716 = v4716_tmp;	// L7437
          w = v4716;	// L7438
          int32_t v4717 = dcred[0];	// L7439
          ac_int<33, true> v4718 = v4717;	// L7440
          ac_int<33, true> v4719 = v4718 - 1;	// L7441
          int32_t v4720 = v4719;	// L7442
          dcred[0] = v4720;	// L7443
          int32_t v4721 = sp[0];	// L7444
          ac_int<33, true> v4722 = v4721;	// L7445
          ac_int<33, true> v4723 = v4722 + 1;	// L7446
          int32_t v4724 = v4723;	// L7447
          sp[0] = v4724;	// L7448
        }
      }
    }
    ac_int<17, true> v4725 = w;	// L7452
    v4666.write(v4725);	// L7453
    int32_t v4726 = v4669.read();	// L7454
    int32_t v4727 = dcred[1];	// L7455
    ac_int<33, true> v4728 = v4727;	// L7456
    ac_int<33, true> v4729 = v4726;	// L7457
    ac_int<33, true> v4730 = v4728 + v4729;	// L7458
    int32_t v4731 = v4730;	// L7459
    dcred[1] = v4731;	// L7460
    ac_int<17, false> w1;	// L7461
    w1 = 0;	// L7462
    int32_t v4733 = sp[1];	// L7463
    bool v4734 = v4733 < 10;	// L7464
    ac_int<33, true> v4735 = v4733;	// L7467
    bool v4736 = v4695 >= v4735;	// L7468
    bool v4737 = v4734 & v4736;	// L7469
    if (v4737) {	// L7470
      int32_t v4738 = sp[1];	// L7471
      int v4739 = v4738;	// L7472
      int32_t v4740 = v4665[1][v4739];	// L7473
      bool v4741 = v4740 == 0;	// L7474
      if (v4741) {	// L7475
        int32_t v4742 = sp[1];	// L7476
        ac_int<33, true> v4743 = v4742;	// L7477
        ac_int<33, true> v4744 = v4743 + 1;	// L7478
        int32_t v4745 = v4744;	// L7479
        sp[1] = v4745;	// L7480
      } else {
        int32_t v4746 = dcred[1];	// L7482
        bool v4747 = v4746 > 0;	// L7483
        if (v4747) {	// L7484
          ac_int<17, true> v4748 = w1;	// L7485
          ac_int<17, true> v4749;
          ap_int<17> v4749_tmp = v4748;
          v4749_tmp[0] = 1;          v4749 = v4749_tmp;	// L7486
          w1 = v4749;	// L7487
          int32_t v4750 = sp[1];	// L7488
          int v4751 = v4750;	// L7489
          half v4752 = v4664[1][v4751];	// L7490
          uint16_t v4753;
          union { half from; uint16_t to;} _converter_v4752_to_v4753 = {};
          _converter_v4752_to_v4753.from = v4752;
          v4753 = _converter_v4752_to_v4753.to;	// L7491
          ac_int<17, true> v4754 = w1;	// L7492
          ac_int<17, true> v4755;
          ap_int<17> v4755_tmp = v4754;
          v4755_tmp(16, 1) = v4753;
          v4755 = v4755_tmp;	// L7493
          w1 = v4755;	// L7494
          int32_t v4756 = dcred[1];	// L7495
          ac_int<33, true> v4757 = v4756;	// L7496
          ac_int<33, true> v4758 = v4757 - 1;	// L7497
          int32_t v4759 = v4758;	// L7498
          dcred[1] = v4759;	// L7499
          int32_t v4760 = sp[1];	// L7500
          ac_int<33, true> v4761 = v4760;	// L7501
          ac_int<33, true> v4762 = v4761 + 1;	// L7502
          int32_t v4763 = v4762;	// L7503
          sp[1] = v4763;	// L7504
        }
      }
    }
    ac_int<17, true> v4764 = w1;	// L7508
    v4667.write(v4764);	// L7509
  }
}

void drv_e_0(
  half v4765[2][10],
  int32_t v4766[2][10],
  ac_channel< ac_int<17, false> >& v4767,
  ac_channel< ac_int<17, false> >& v4768,
  ac_channel< int32_t >& v4769,
  ac_channel< int32_t >& v4770
) {	// L7513
  int32_t dcred1[2];	// L7522
  for (int v4772 = 0; v4772 < 2; v4772++) {	// L7523
    dcred1[v4772] = 0;	// L7523
  }
  int32_t sp1[2];	// L7524
  for (int v4774 = 0; v4774 < 2; v4774++) {	// L7525
    sp1[v4774] = 0;	// L7525
  }
  ac_int<17, false> zw1;	// L7526
  zw1 = 0;	// L7527
  ac_int<17, true> v4776 = zw1;	// L7528
  v4767.write(v4776);	// L7529
  ac_int<17, true> v4777 = zw1;	// L7530
  v4768.write(v4777);	// L7531
  ac_int<17, true> v4778 = zw1;	// L7532
  v4767.write(v4778);	// L7533
  ac_int<17, true> v4779 = zw1;	// L7534
  v4768.write(v4779);	// L7535
  ac_int<17, true> v4780 = zw1;	// L7536
  v4767.write(v4780);	// L7537
  ac_int<17, true> v4781 = zw1;	// L7538
  v4768.write(v4781);	// L7539
  ac_int<17, true> v4782 = zw1;	// L7540
  v4767.write(v4782);	// L7541
  ac_int<17, true> v4783 = zw1;	// L7542
  v4768.write(v4783);	// L7543
  ac_int<17, true> v4784 = zw1;	// L7544
  v4767.write(v4784);	// L7545
  ac_int<17, true> v4785 = zw1;	// L7546
  v4768.write(v4785);	// L7547
  l_S_t_0_t5: for (int t5 = 0; t5 < 10; t5++) {	// L7548
    int32_t v4787 = v4769.read();	// L7549
    int32_t v4788 = dcred1[0];	// L7550
    ac_int<33, true> v4789 = v4788;	// L7551
    ac_int<33, true> v4790 = v4787;	// L7552
    ac_int<33, true> v4791 = v4789 + v4790;	// L7553
    int32_t v4792 = v4791;	// L7554
    dcred1[0] = v4792;	// L7555
    ac_int<17, false> w2;	// L7556
    w2 = 0;	// L7557
    int32_t v4794 = sp1[0];	// L7558
    bool v4795 = v4794 < 10;	// L7559
    ac_int<33, true> v4796 = t5;	// L7561
    ac_int<33, true> v4797 = v4794;	// L7562
    bool v4798 = v4796 >= v4797;	// L7563
    bool v4799 = v4795 & v4798;	// L7564
    if (v4799) {	// L7565
      int32_t v4800 = sp1[0];	// L7566
      int v4801 = v4800;	// L7567
      int32_t v4802 = v4766[0][v4801];	// L7568
      bool v4803 = v4802 == 0;	// L7569
      if (v4803) {	// L7570
        int32_t v4804 = sp1[0];	// L7571
        ac_int<33, true> v4805 = v4804;	// L7572
        ac_int<33, true> v4806 = v4805 + 1;	// L7573
        int32_t v4807 = v4806;	// L7574
        sp1[0] = v4807;	// L7575
      } else {
        int32_t v4808 = dcred1[0];	// L7577
        bool v4809 = v4808 > 0;	// L7578
        if (v4809) {	// L7579
          ac_int<17, true> v4810 = w2;	// L7580
          ac_int<17, true> v4811;
          ap_int<17> v4811_tmp = v4810;
          v4811_tmp[0] = 1;          v4811 = v4811_tmp;	// L7581
          w2 = v4811;	// L7582
          int32_t v4812 = sp1[0];	// L7583
          int v4813 = v4812;	// L7584
          half v4814 = v4765[0][v4813];	// L7585
          uint16_t v4815;
          union { half from; uint16_t to;} _converter_v4814_to_v4815 = {};
          _converter_v4814_to_v4815.from = v4814;
          v4815 = _converter_v4814_to_v4815.to;	// L7586
          ac_int<17, true> v4816 = w2;	// L7587
          ac_int<17, true> v4817;
          ap_int<17> v4817_tmp = v4816;
          v4817_tmp(16, 1) = v4815;
          v4817 = v4817_tmp;	// L7588
          w2 = v4817;	// L7589
          int32_t v4818 = dcred1[0];	// L7590
          ac_int<33, true> v4819 = v4818;	// L7591
          ac_int<33, true> v4820 = v4819 - 1;	// L7592
          int32_t v4821 = v4820;	// L7593
          dcred1[0] = v4821;	// L7594
          int32_t v4822 = sp1[0];	// L7595
          ac_int<33, true> v4823 = v4822;	// L7596
          ac_int<33, true> v4824 = v4823 + 1;	// L7597
          int32_t v4825 = v4824;	// L7598
          sp1[0] = v4825;	// L7599
        }
      }
    }
    ac_int<17, true> v4826 = w2;	// L7603
    v4767.write(v4826);	// L7604
    int32_t v4827 = v4770.read();	// L7605
    int32_t v4828 = dcred1[1];	// L7606
    ac_int<33, true> v4829 = v4828;	// L7607
    ac_int<33, true> v4830 = v4827;	// L7608
    ac_int<33, true> v4831 = v4829 + v4830;	// L7609
    int32_t v4832 = v4831;	// L7610
    dcred1[1] = v4832;	// L7611
    ac_int<17, false> w3;	// L7612
    w3 = 0;	// L7613
    int32_t v4834 = sp1[1];	// L7614
    bool v4835 = v4834 < 10;	// L7615
    ac_int<33, true> v4836 = v4834;	// L7618
    bool v4837 = v4796 >= v4836;	// L7619
    bool v4838 = v4835 & v4837;	// L7620
    if (v4838) {	// L7621
      int32_t v4839 = sp1[1];	// L7622
      int v4840 = v4839;	// L7623
      int32_t v4841 = v4766[1][v4840];	// L7624
      bool v4842 = v4841 == 0;	// L7625
      if (v4842) {	// L7626
        int32_t v4843 = sp1[1];	// L7627
        ac_int<33, true> v4844 = v4843;	// L7628
        ac_int<33, true> v4845 = v4844 + 1;	// L7629
        int32_t v4846 = v4845;	// L7630
        sp1[1] = v4846;	// L7631
      } else {
        int32_t v4847 = dcred1[1];	// L7633
        bool v4848 = v4847 > 0;	// L7634
        if (v4848) {	// L7635
          ac_int<17, true> v4849 = w3;	// L7636
          ac_int<17, true> v4850;
          ap_int<17> v4850_tmp = v4849;
          v4850_tmp[0] = 1;          v4850 = v4850_tmp;	// L7637
          w3 = v4850;	// L7638
          int32_t v4851 = sp1[1];	// L7639
          int v4852 = v4851;	// L7640
          half v4853 = v4765[1][v4852];	// L7641
          uint16_t v4854;
          union { half from; uint16_t to;} _converter_v4853_to_v4854 = {};
          _converter_v4853_to_v4854.from = v4853;
          v4854 = _converter_v4853_to_v4854.to;	// L7642
          ac_int<17, true> v4855 = w3;	// L7643
          ac_int<17, true> v4856;
          ap_int<17> v4856_tmp = v4855;
          v4856_tmp(16, 1) = v4854;
          v4856 = v4856_tmp;	// L7644
          w3 = v4856;	// L7645
          int32_t v4857 = dcred1[1];	// L7646
          ac_int<33, true> v4858 = v4857;	// L7647
          ac_int<33, true> v4859 = v4858 - 1;	// L7648
          int32_t v4860 = v4859;	// L7649
          dcred1[1] = v4860;	// L7650
          int32_t v4861 = sp1[1];	// L7651
          ac_int<33, true> v4862 = v4861;	// L7652
          ac_int<33, true> v4863 = v4862 + 1;	// L7653
          int32_t v4864 = v4863;	// L7654
          sp1[1] = v4864;	// L7655
        }
      }
    }
    ac_int<17, true> v4865 = w3;	// L7659
    v4768.write(v4865);	// L7660
  }
}

void drv_n_0(
  half v4866[2][10],
  int32_t v4867[2][10],
  ac_channel< ac_int<17, false> >& v4868,
  ac_channel< ac_int<17, false> >& v4869,
  ac_channel< int32_t >& v4870,
  ac_channel< int32_t >& v4871
) {	// L7664
  int32_t dcred2[2];	// L7673
  for (int v4873 = 0; v4873 < 2; v4873++) {	// L7674
    dcred2[v4873] = 0;	// L7674
  }
  int32_t sp2[2];	// L7675
  for (int v4875 = 0; v4875 < 2; v4875++) {	// L7676
    sp2[v4875] = 0;	// L7676
  }
  ac_int<17, false> zw2;	// L7677
  zw2 = 0;	// L7678
  ac_int<17, true> v4877 = zw2;	// L7679
  v4868.write(v4877);	// L7680
  ac_int<17, true> v4878 = zw2;	// L7681
  v4869.write(v4878);	// L7682
  ac_int<17, true> v4879 = zw2;	// L7683
  v4868.write(v4879);	// L7684
  ac_int<17, true> v4880 = zw2;	// L7685
  v4869.write(v4880);	// L7686
  ac_int<17, true> v4881 = zw2;	// L7687
  v4868.write(v4881);	// L7688
  ac_int<17, true> v4882 = zw2;	// L7689
  v4869.write(v4882);	// L7690
  ac_int<17, true> v4883 = zw2;	// L7691
  v4868.write(v4883);	// L7692
  ac_int<17, true> v4884 = zw2;	// L7693
  v4869.write(v4884);	// L7694
  ac_int<17, true> v4885 = zw2;	// L7695
  v4868.write(v4885);	// L7696
  ac_int<17, true> v4886 = zw2;	// L7697
  v4869.write(v4886);	// L7698
  l_S_t_0_t6: for (int t6 = 0; t6 < 10; t6++) {	// L7699
    int32_t v4888 = v4870.read();	// L7700
    int32_t v4889 = dcred2[0];	// L7701
    ac_int<33, true> v4890 = v4889;	// L7702
    ac_int<33, true> v4891 = v4888;	// L7703
    ac_int<33, true> v4892 = v4890 + v4891;	// L7704
    int32_t v4893 = v4892;	// L7705
    dcred2[0] = v4893;	// L7706
    ac_int<17, false> w4;	// L7707
    w4 = 0;	// L7708
    int32_t v4895 = sp2[0];	// L7709
    bool v4896 = v4895 < 10;	// L7710
    ac_int<33, true> v4897 = t6;	// L7712
    ac_int<33, true> v4898 = v4895;	// L7713
    bool v4899 = v4897 >= v4898;	// L7714
    bool v4900 = v4896 & v4899;	// L7715
    if (v4900) {	// L7716
      int32_t v4901 = sp2[0];	// L7717
      int v4902 = v4901;	// L7718
      int32_t v4903 = v4867[0][v4902];	// L7719
      bool v4904 = v4903 == 0;	// L7720
      if (v4904) {	// L7721
        int32_t v4905 = sp2[0];	// L7722
        ac_int<33, true> v4906 = v4905;	// L7723
        ac_int<33, true> v4907 = v4906 + 1;	// L7724
        int32_t v4908 = v4907;	// L7725
        sp2[0] = v4908;	// L7726
      } else {
        int32_t v4909 = dcred2[0];	// L7728
        bool v4910 = v4909 > 0;	// L7729
        if (v4910) {	// L7730
          ac_int<17, true> v4911 = w4;	// L7731
          ac_int<17, true> v4912;
          ap_int<17> v4912_tmp = v4911;
          v4912_tmp[0] = 1;          v4912 = v4912_tmp;	// L7732
          w4 = v4912;	// L7733
          int32_t v4913 = sp2[0];	// L7734
          int v4914 = v4913;	// L7735
          half v4915 = v4866[0][v4914];	// L7736
          uint16_t v4916;
          union { half from; uint16_t to;} _converter_v4915_to_v4916 = {};
          _converter_v4915_to_v4916.from = v4915;
          v4916 = _converter_v4915_to_v4916.to;	// L7737
          ac_int<17, true> v4917 = w4;	// L7738
          ac_int<17, true> v4918;
          ap_int<17> v4918_tmp = v4917;
          v4918_tmp(16, 1) = v4916;
          v4918 = v4918_tmp;	// L7739
          w4 = v4918;	// L7740
          int32_t v4919 = dcred2[0];	// L7741
          ac_int<33, true> v4920 = v4919;	// L7742
          ac_int<33, true> v4921 = v4920 - 1;	// L7743
          int32_t v4922 = v4921;	// L7744
          dcred2[0] = v4922;	// L7745
          int32_t v4923 = sp2[0];	// L7746
          ac_int<33, true> v4924 = v4923;	// L7747
          ac_int<33, true> v4925 = v4924 + 1;	// L7748
          int32_t v4926 = v4925;	// L7749
          sp2[0] = v4926;	// L7750
        }
      }
    }
    ac_int<17, true> v4927 = w4;	// L7754
    v4868.write(v4927);	// L7755
    int32_t v4928 = v4871.read();	// L7756
    int32_t v4929 = dcred2[1];	// L7757
    ac_int<33, true> v4930 = v4929;	// L7758
    ac_int<33, true> v4931 = v4928;	// L7759
    ac_int<33, true> v4932 = v4930 + v4931;	// L7760
    int32_t v4933 = v4932;	// L7761
    dcred2[1] = v4933;	// L7762
    ac_int<17, false> w5;	// L7763
    w5 = 0;	// L7764
    int32_t v4935 = sp2[1];	// L7765
    bool v4936 = v4935 < 10;	// L7766
    ac_int<33, true> v4937 = v4935;	// L7769
    bool v4938 = v4897 >= v4937;	// L7770
    bool v4939 = v4936 & v4938;	// L7771
    if (v4939) {	// L7772
      int32_t v4940 = sp2[1];	// L7773
      int v4941 = v4940;	// L7774
      int32_t v4942 = v4867[1][v4941];	// L7775
      bool v4943 = v4942 == 0;	// L7776
      if (v4943) {	// L7777
        int32_t v4944 = sp2[1];	// L7778
        ac_int<33, true> v4945 = v4944;	// L7779
        ac_int<33, true> v4946 = v4945 + 1;	// L7780
        int32_t v4947 = v4946;	// L7781
        sp2[1] = v4947;	// L7782
      } else {
        int32_t v4948 = dcred2[1];	// L7784
        bool v4949 = v4948 > 0;	// L7785
        if (v4949) {	// L7786
          ac_int<17, true> v4950 = w5;	// L7787
          ac_int<17, true> v4951;
          ap_int<17> v4951_tmp = v4950;
          v4951_tmp[0] = 1;          v4951 = v4951_tmp;	// L7788
          w5 = v4951;	// L7789
          int32_t v4952 = sp2[1];	// L7790
          int v4953 = v4952;	// L7791
          half v4954 = v4866[1][v4953];	// L7792
          uint16_t v4955;
          union { half from; uint16_t to;} _converter_v4954_to_v4955 = {};
          _converter_v4954_to_v4955.from = v4954;
          v4955 = _converter_v4954_to_v4955.to;	// L7793
          ac_int<17, true> v4956 = w5;	// L7794
          ac_int<17, true> v4957;
          ap_int<17> v4957_tmp = v4956;
          v4957_tmp(16, 1) = v4955;
          v4957 = v4957_tmp;	// L7795
          w5 = v4957;	// L7796
          int32_t v4958 = dcred2[1];	// L7797
          ac_int<33, true> v4959 = v4958;	// L7798
          ac_int<33, true> v4960 = v4959 - 1;	// L7799
          int32_t v4961 = v4960;	// L7800
          dcred2[1] = v4961;	// L7801
          int32_t v4962 = sp2[1];	// L7802
          ac_int<33, true> v4963 = v4962;	// L7803
          ac_int<33, true> v4964 = v4963 + 1;	// L7804
          int32_t v4965 = v4964;	// L7805
          sp2[1] = v4965;	// L7806
        }
      }
    }
    ac_int<17, true> v4966 = w5;	// L7810
    v4869.write(v4966);	// L7811
  }
}

void drv_s_0(
  half v4967[2][10],
  int32_t v4968[2][10],
  ac_channel< ac_int<17, false> >& v4969,
  ac_channel< ac_int<17, false> >& v4970,
  ac_channel< int32_t >& v4971,
  ac_channel< int32_t >& v4972
) {	// L7815
  int32_t dcred3[2];	// L7824
  for (int v4974 = 0; v4974 < 2; v4974++) {	// L7825
    dcred3[v4974] = 0;	// L7825
  }
  int32_t sp3[2];	// L7826
  for (int v4976 = 0; v4976 < 2; v4976++) {	// L7827
    sp3[v4976] = 0;	// L7827
  }
  ac_int<17, false> zw3;	// L7828
  zw3 = 0;	// L7829
  ac_int<17, true> v4978 = zw3;	// L7830
  v4969.write(v4978);	// L7831
  ac_int<17, true> v4979 = zw3;	// L7832
  v4970.write(v4979);	// L7833
  ac_int<17, true> v4980 = zw3;	// L7834
  v4969.write(v4980);	// L7835
  ac_int<17, true> v4981 = zw3;	// L7836
  v4970.write(v4981);	// L7837
  ac_int<17, true> v4982 = zw3;	// L7838
  v4969.write(v4982);	// L7839
  ac_int<17, true> v4983 = zw3;	// L7840
  v4970.write(v4983);	// L7841
  ac_int<17, true> v4984 = zw3;	// L7842
  v4969.write(v4984);	// L7843
  ac_int<17, true> v4985 = zw3;	// L7844
  v4970.write(v4985);	// L7845
  ac_int<17, true> v4986 = zw3;	// L7846
  v4969.write(v4986);	// L7847
  ac_int<17, true> v4987 = zw3;	// L7848
  v4970.write(v4987);	// L7849
  l_S_t_0_t7: for (int t7 = 0; t7 < 10; t7++) {	// L7850
    int32_t v4989 = v4971.read();	// L7851
    int32_t v4990 = dcred3[0];	// L7852
    ac_int<33, true> v4991 = v4990;	// L7853
    ac_int<33, true> v4992 = v4989;	// L7854
    ac_int<33, true> v4993 = v4991 + v4992;	// L7855
    int32_t v4994 = v4993;	// L7856
    dcred3[0] = v4994;	// L7857
    ac_int<17, false> w6;	// L7858
    w6 = 0;	// L7859
    int32_t v4996 = sp3[0];	// L7860
    bool v4997 = v4996 < 10;	// L7861
    ac_int<33, true> v4998 = t7;	// L7863
    ac_int<33, true> v4999 = v4996;	// L7864
    bool v5000 = v4998 >= v4999;	// L7865
    bool v5001 = v4997 & v5000;	// L7866
    if (v5001) {	// L7867
      int32_t v5002 = sp3[0];	// L7868
      int v5003 = v5002;	// L7869
      int32_t v5004 = v4968[0][v5003];	// L7870
      bool v5005 = v5004 == 0;	// L7871
      if (v5005) {	// L7872
        int32_t v5006 = sp3[0];	// L7873
        ac_int<33, true> v5007 = v5006;	// L7874
        ac_int<33, true> v5008 = v5007 + 1;	// L7875
        int32_t v5009 = v5008;	// L7876
        sp3[0] = v5009;	// L7877
      } else {
        int32_t v5010 = dcred3[0];	// L7879
        bool v5011 = v5010 > 0;	// L7880
        if (v5011) {	// L7881
          ac_int<17, true> v5012 = w6;	// L7882
          ac_int<17, true> v5013;
          ap_int<17> v5013_tmp = v5012;
          v5013_tmp[0] = 1;          v5013 = v5013_tmp;	// L7883
          w6 = v5013;	// L7884
          int32_t v5014 = sp3[0];	// L7885
          int v5015 = v5014;	// L7886
          half v5016 = v4967[0][v5015];	// L7887
          uint16_t v5017;
          union { half from; uint16_t to;} _converter_v5016_to_v5017 = {};
          _converter_v5016_to_v5017.from = v5016;
          v5017 = _converter_v5016_to_v5017.to;	// L7888
          ac_int<17, true> v5018 = w6;	// L7889
          ac_int<17, true> v5019;
          ap_int<17> v5019_tmp = v5018;
          v5019_tmp(16, 1) = v5017;
          v5019 = v5019_tmp;	// L7890
          w6 = v5019;	// L7891
          int32_t v5020 = dcred3[0];	// L7892
          ac_int<33, true> v5021 = v5020;	// L7893
          ac_int<33, true> v5022 = v5021 - 1;	// L7894
          int32_t v5023 = v5022;	// L7895
          dcred3[0] = v5023;	// L7896
          int32_t v5024 = sp3[0];	// L7897
          ac_int<33, true> v5025 = v5024;	// L7898
          ac_int<33, true> v5026 = v5025 + 1;	// L7899
          int32_t v5027 = v5026;	// L7900
          sp3[0] = v5027;	// L7901
        }
      }
    }
    ac_int<17, true> v5028 = w6;	// L7905
    v4969.write(v5028);	// L7906
    int32_t v5029 = v4972.read();	// L7907
    int32_t v5030 = dcred3[1];	// L7908
    ac_int<33, true> v5031 = v5030;	// L7909
    ac_int<33, true> v5032 = v5029;	// L7910
    ac_int<33, true> v5033 = v5031 + v5032;	// L7911
    int32_t v5034 = v5033;	// L7912
    dcred3[1] = v5034;	// L7913
    ac_int<17, false> w7;	// L7914
    w7 = 0;	// L7915
    int32_t v5036 = sp3[1];	// L7916
    bool v5037 = v5036 < 10;	// L7917
    ac_int<33, true> v5038 = v5036;	// L7920
    bool v5039 = v4998 >= v5038;	// L7921
    bool v5040 = v5037 & v5039;	// L7922
    if (v5040) {	// L7923
      int32_t v5041 = sp3[1];	// L7924
      int v5042 = v5041;	// L7925
      int32_t v5043 = v4968[1][v5042];	// L7926
      bool v5044 = v5043 == 0;	// L7927
      if (v5044) {	// L7928
        int32_t v5045 = sp3[1];	// L7929
        ac_int<33, true> v5046 = v5045;	// L7930
        ac_int<33, true> v5047 = v5046 + 1;	// L7931
        int32_t v5048 = v5047;	// L7932
        sp3[1] = v5048;	// L7933
      } else {
        int32_t v5049 = dcred3[1];	// L7935
        bool v5050 = v5049 > 0;	// L7936
        if (v5050) {	// L7937
          ac_int<17, true> v5051 = w7;	// L7938
          ac_int<17, true> v5052;
          ap_int<17> v5052_tmp = v5051;
          v5052_tmp[0] = 1;          v5052 = v5052_tmp;	// L7939
          w7 = v5052;	// L7940
          int32_t v5053 = sp3[1];	// L7941
          int v5054 = v5053;	// L7942
          half v5055 = v4967[1][v5054];	// L7943
          uint16_t v5056;
          union { half from; uint16_t to;} _converter_v5055_to_v5056 = {};
          _converter_v5055_to_v5056.from = v5055;
          v5056 = _converter_v5055_to_v5056.to;	// L7944
          ac_int<17, true> v5057 = w7;	// L7945
          ac_int<17, true> v5058;
          ap_int<17> v5058_tmp = v5057;
          v5058_tmp(16, 1) = v5056;
          v5058 = v5058_tmp;	// L7946
          w7 = v5058;	// L7947
          int32_t v5059 = dcred3[1];	// L7948
          ac_int<33, true> v5060 = v5059;	// L7949
          ac_int<33, true> v5061 = v5060 - 1;	// L7950
          int32_t v5062 = v5061;	// L7951
          dcred3[1] = v5062;	// L7952
          int32_t v5063 = sp3[1];	// L7953
          ac_int<33, true> v5064 = v5063;	// L7954
          ac_int<33, true> v5065 = v5064 + 1;	// L7955
          int32_t v5066 = v5065;	// L7956
          sp3[1] = v5066;	// L7957
        }
      }
    }
    ac_int<17, true> v5067 = w7;	// L7961
    v4970.write(v5067);	// L7962
  }
}

void col_w_0(
  half v5068[2][10],
  ac_channel< int32_t >& v5069,
  ac_channel< int32_t >& v5070,
  ac_channel< ac_int<17, false> >& v5071,
  ac_channel< ac_int<17, false> >& v5072
) {	// L7966
  int32_t k8[2];	// L7975
  for (int v5074 = 0; v5074 < 2; v5074++) {	// L7976
    k8[v5074] = 0;	// L7976
  }
  int32_t cret[2];	// L7977
  for (int v5076 = 0; v5076 < 2; v5076++) {	// L7978
    cret[v5076] = 0;	// L7978
  }
  int32_t zc;	// L7979
  zc = 0;	// L7980
  int32_t v5078 = zc;	// L7981
  v5069.write(v5078);	// L7982
  int32_t v5079 = zc;	// L7983
  v5070.write(v5079);	// L7984
  int32_t v5080 = zc;	// L7985
  v5069.write(v5080);	// L7986
  int32_t v5081 = zc;	// L7987
  v5070.write(v5081);	// L7988
  int32_t v5082 = zc;	// L7989
  v5069.write(v5082);	// L7990
  int32_t v5083 = zc;	// L7991
  v5070.write(v5083);	// L7992
  int32_t v5084 = zc;	// L7993
  v5069.write(v5084);	// L7994
  int32_t v5085 = zc;	// L7995
  v5070.write(v5085);	// L7996
  int32_t v5086 = zc;	// L7997
  v5069.write(v5086);	// L7998
  int32_t v5087 = zc;	// L7999
  v5070.write(v5087);	// L8000
  cret[0] = 2;	// L8001
  int32_t v5088 = cret[0];	// L8002
  v5069.write(v5088);	// L8003
  cret[1] = 2;	// L8004
  int32_t v5089 = cret[1];	// L8005
  v5070.write(v5089);	// L8006
  l_S_t_0_t8: for (int t8 = 0; t8 < 10; t8++) {	// L8007
    ac_int<17, false> v5091 = v5071.read();	// L8008
    ac_int<17, false> w8;	// L8009
    w8 = v5091;	// L8010
    cret[0] = 0;	// L8011
    ac_int<17, true> v5093 = w8;	// L8012
    bool v5094;
    ap_int<17> v5094_tmp = v5093;
    v5094 = v5094_tmp[0];	// L8013
    int32_t v5095 = v5094;	// L8014
    bool v5096 = v5095 == 1;	// L8015
    if (v5096) {	// L8016
      cret[0] = 1;	// L8017
      int32_t v5097 = k8[0];	// L8018
      bool v5098 = v5097 < 10;	// L8019
      if (v5098) {	// L8020
        ac_int<17, true> v5099 = w8;	// L8021
        int16_t v5100;
        ap_int<17> v5100_tmp = v5099;
        v5100 = v5100_tmp(16, 1);	// L8022
        half v5101;
        union { uint16_t from; half to;} _converter_v5100_to_v5101 = {};
        _converter_v5100_to_v5101.from = v5100;
        v5101 = _converter_v5100_to_v5101.to;	// L8023
        int32_t v5102 = k8[0];	// L8024
        int v5103 = v5102;	// L8025
        v5068[0][v5103] = v5101;	// L8026
        int32_t v5104 = k8[0];	// L8027
        ac_int<33, true> v5105 = v5104;	// L8028
        ac_int<33, true> v5106 = v5105 + 1;	// L8029
        int32_t v5107 = v5106;	// L8030
        k8[0] = v5107;	// L8031
      }
    }
    int32_t v5108 = cret[0];	// L8034
    v5069.write(v5108);	// L8035
    ac_int<17, false> v5109 = v5072.read();	// L8036
    ac_int<17, false> w9;	// L8037
    w9 = v5109;	// L8038
    cret[1] = 0;	// L8039
    ac_int<17, true> v5111 = w9;	// L8040
    bool v5112;
    ap_int<17> v5112_tmp = v5111;
    v5112 = v5112_tmp[0];	// L8041
    int32_t v5113 = v5112;	// L8042
    bool v5114 = v5113 == 1;	// L8043
    if (v5114) {	// L8044
      cret[1] = 1;	// L8045
      int32_t v5115 = k8[1];	// L8046
      bool v5116 = v5115 < 10;	// L8047
      if (v5116) {	// L8048
        ac_int<17, true> v5117 = w9;	// L8049
        int16_t v5118;
        ap_int<17> v5118_tmp = v5117;
        v5118 = v5118_tmp(16, 1);	// L8050
        half v5119;
        union { uint16_t from; half to;} _converter_v5118_to_v5119 = {};
        _converter_v5118_to_v5119.from = v5118;
        v5119 = _converter_v5118_to_v5119.to;	// L8051
        int32_t v5120 = k8[1];	// L8052
        int v5121 = v5120;	// L8053
        v5068[1][v5121] = v5119;	// L8054
        int32_t v5122 = k8[1];	// L8055
        ac_int<33, true> v5123 = v5122;	// L8056
        ac_int<33, true> v5124 = v5123 + 1;	// L8057
        int32_t v5125 = v5124;	// L8058
        k8[1] = v5125;	// L8059
      }
    }
    int32_t v5126 = cret[1];	// L8062
    v5070.write(v5126);	// L8063
  }
}

void col_e_0(
  half v5127[2][10],
  ac_channel< int32_t >& v5128,
  ac_channel< int32_t >& v5129,
  ac_channel< ac_int<17, false> >& v5130,
  ac_channel< ac_int<17, false> >& v5131
) {	// L8067
  int32_t k9[2];	// L8076
  for (int v5133 = 0; v5133 < 2; v5133++) {	// L8077
    k9[v5133] = 0;	// L8077
  }
  int32_t cret1[2];	// L8078
  for (int v5135 = 0; v5135 < 2; v5135++) {	// L8079
    cret1[v5135] = 0;	// L8079
  }
  int32_t zc1;	// L8080
  zc1 = 0;	// L8081
  int32_t v5137 = zc1;	// L8082
  v5128.write(v5137);	// L8083
  int32_t v5138 = zc1;	// L8084
  v5129.write(v5138);	// L8085
  int32_t v5139 = zc1;	// L8086
  v5128.write(v5139);	// L8087
  int32_t v5140 = zc1;	// L8088
  v5129.write(v5140);	// L8089
  int32_t v5141 = zc1;	// L8090
  v5128.write(v5141);	// L8091
  int32_t v5142 = zc1;	// L8092
  v5129.write(v5142);	// L8093
  int32_t v5143 = zc1;	// L8094
  v5128.write(v5143);	// L8095
  int32_t v5144 = zc1;	// L8096
  v5129.write(v5144);	// L8097
  int32_t v5145 = zc1;	// L8098
  v5128.write(v5145);	// L8099
  int32_t v5146 = zc1;	// L8100
  v5129.write(v5146);	// L8101
  cret1[0] = 2;	// L8102
  int32_t v5147 = cret1[0];	// L8103
  v5128.write(v5147);	// L8104
  cret1[1] = 2;	// L8105
  int32_t v5148 = cret1[1];	// L8106
  v5129.write(v5148);	// L8107
  l_S_t_0_t9: for (int t9 = 0; t9 < 10; t9++) {	// L8108
    ac_int<17, false> v5150 = v5130.read();	// L8109
    ac_int<17, false> w10;	// L8110
    w10 = v5150;	// L8111
    cret1[0] = 0;	// L8112
    ac_int<17, true> v5152 = w10;	// L8113
    bool v5153;
    ap_int<17> v5153_tmp = v5152;
    v5153 = v5153_tmp[0];	// L8114
    int32_t v5154 = v5153;	// L8115
    bool v5155 = v5154 == 1;	// L8116
    if (v5155) {	// L8117
      cret1[0] = 1;	// L8118
      int32_t v5156 = k9[0];	// L8119
      bool v5157 = v5156 < 10;	// L8120
      if (v5157) {	// L8121
        ac_int<17, true> v5158 = w10;	// L8122
        int16_t v5159;
        ap_int<17> v5159_tmp = v5158;
        v5159 = v5159_tmp(16, 1);	// L8123
        half v5160;
        union { uint16_t from; half to;} _converter_v5159_to_v5160 = {};
        _converter_v5159_to_v5160.from = v5159;
        v5160 = _converter_v5159_to_v5160.to;	// L8124
        int32_t v5161 = k9[0];	// L8125
        int v5162 = v5161;	// L8126
        v5127[0][v5162] = v5160;	// L8127
        int32_t v5163 = k9[0];	// L8128
        ac_int<33, true> v5164 = v5163;	// L8129
        ac_int<33, true> v5165 = v5164 + 1;	// L8130
        int32_t v5166 = v5165;	// L8131
        k9[0] = v5166;	// L8132
      }
    }
    int32_t v5167 = cret1[0];	// L8135
    v5128.write(v5167);	// L8136
    ac_int<17, false> v5168 = v5131.read();	// L8137
    ac_int<17, false> w11;	// L8138
    w11 = v5168;	// L8139
    cret1[1] = 0;	// L8140
    ac_int<17, true> v5170 = w11;	// L8141
    bool v5171;
    ap_int<17> v5171_tmp = v5170;
    v5171 = v5171_tmp[0];	// L8142
    int32_t v5172 = v5171;	// L8143
    bool v5173 = v5172 == 1;	// L8144
    if (v5173) {	// L8145
      cret1[1] = 1;	// L8146
      int32_t v5174 = k9[1];	// L8147
      bool v5175 = v5174 < 10;	// L8148
      if (v5175) {	// L8149
        ac_int<17, true> v5176 = w11;	// L8150
        int16_t v5177;
        ap_int<17> v5177_tmp = v5176;
        v5177 = v5177_tmp(16, 1);	// L8151
        half v5178;
        union { uint16_t from; half to;} _converter_v5177_to_v5178 = {};
        _converter_v5177_to_v5178.from = v5177;
        v5178 = _converter_v5177_to_v5178.to;	// L8152
        int32_t v5179 = k9[1];	// L8153
        int v5180 = v5179;	// L8154
        v5127[1][v5180] = v5178;	// L8155
        int32_t v5181 = k9[1];	// L8156
        ac_int<33, true> v5182 = v5181;	// L8157
        ac_int<33, true> v5183 = v5182 + 1;	// L8158
        int32_t v5184 = v5183;	// L8159
        k9[1] = v5184;	// L8160
      }
    }
    int32_t v5185 = cret1[1];	// L8163
    v5129.write(v5185);	// L8164
  }
}

void col_n_0(
  half v5186[2][10],
  ac_channel< int32_t >& v5187,
  ac_channel< int32_t >& v5188,
  ac_channel< ac_int<17, false> >& v5189,
  ac_channel< ac_int<17, false> >& v5190
) {	// L8168
  int32_t k10[2];	// L8177
  for (int v5192 = 0; v5192 < 2; v5192++) {	// L8178
    k10[v5192] = 0;	// L8178
  }
  int32_t cret2[2];	// L8179
  for (int v5194 = 0; v5194 < 2; v5194++) {	// L8180
    cret2[v5194] = 0;	// L8180
  }
  int32_t zc2;	// L8181
  zc2 = 0;	// L8182
  int32_t v5196 = zc2;	// L8183
  v5187.write(v5196);	// L8184
  int32_t v5197 = zc2;	// L8185
  v5188.write(v5197);	// L8186
  int32_t v5198 = zc2;	// L8187
  v5187.write(v5198);	// L8188
  int32_t v5199 = zc2;	// L8189
  v5188.write(v5199);	// L8190
  int32_t v5200 = zc2;	// L8191
  v5187.write(v5200);	// L8192
  int32_t v5201 = zc2;	// L8193
  v5188.write(v5201);	// L8194
  int32_t v5202 = zc2;	// L8195
  v5187.write(v5202);	// L8196
  int32_t v5203 = zc2;	// L8197
  v5188.write(v5203);	// L8198
  int32_t v5204 = zc2;	// L8199
  v5187.write(v5204);	// L8200
  int32_t v5205 = zc2;	// L8201
  v5188.write(v5205);	// L8202
  cret2[0] = 2;	// L8203
  int32_t v5206 = cret2[0];	// L8204
  v5187.write(v5206);	// L8205
  cret2[1] = 2;	// L8206
  int32_t v5207 = cret2[1];	// L8207
  v5188.write(v5207);	// L8208
  l_S_t_0_t10: for (int t10 = 0; t10 < 10; t10++) {	// L8209
    ac_int<17, false> v5209 = v5189.read();	// L8210
    ac_int<17, false> w12;	// L8211
    w12 = v5209;	// L8212
    cret2[0] = 0;	// L8213
    ac_int<17, true> v5211 = w12;	// L8214
    bool v5212;
    ap_int<17> v5212_tmp = v5211;
    v5212 = v5212_tmp[0];	// L8215
    int32_t v5213 = v5212;	// L8216
    bool v5214 = v5213 == 1;	// L8217
    if (v5214) {	// L8218
      cret2[0] = 1;	// L8219
      int32_t v5215 = k10[0];	// L8220
      bool v5216 = v5215 < 10;	// L8221
      if (v5216) {	// L8222
        ac_int<17, true> v5217 = w12;	// L8223
        int16_t v5218;
        ap_int<17> v5218_tmp = v5217;
        v5218 = v5218_tmp(16, 1);	// L8224
        half v5219;
        union { uint16_t from; half to;} _converter_v5218_to_v5219 = {};
        _converter_v5218_to_v5219.from = v5218;
        v5219 = _converter_v5218_to_v5219.to;	// L8225
        int32_t v5220 = k10[0];	// L8226
        int v5221 = v5220;	// L8227
        v5186[0][v5221] = v5219;	// L8228
        int32_t v5222 = k10[0];	// L8229
        ac_int<33, true> v5223 = v5222;	// L8230
        ac_int<33, true> v5224 = v5223 + 1;	// L8231
        int32_t v5225 = v5224;	// L8232
        k10[0] = v5225;	// L8233
      }
    }
    int32_t v5226 = cret2[0];	// L8236
    v5187.write(v5226);	// L8237
    ac_int<17, false> v5227 = v5190.read();	// L8238
    ac_int<17, false> w13;	// L8239
    w13 = v5227;	// L8240
    cret2[1] = 0;	// L8241
    ac_int<17, true> v5229 = w13;	// L8242
    bool v5230;
    ap_int<17> v5230_tmp = v5229;
    v5230 = v5230_tmp[0];	// L8243
    int32_t v5231 = v5230;	// L8244
    bool v5232 = v5231 == 1;	// L8245
    if (v5232) {	// L8246
      cret2[1] = 1;	// L8247
      int32_t v5233 = k10[1];	// L8248
      bool v5234 = v5233 < 10;	// L8249
      if (v5234) {	// L8250
        ac_int<17, true> v5235 = w13;	// L8251
        int16_t v5236;
        ap_int<17> v5236_tmp = v5235;
        v5236 = v5236_tmp(16, 1);	// L8252
        half v5237;
        union { uint16_t from; half to;} _converter_v5236_to_v5237 = {};
        _converter_v5236_to_v5237.from = v5236;
        v5237 = _converter_v5236_to_v5237.to;	// L8253
        int32_t v5238 = k10[1];	// L8254
        int v5239 = v5238;	// L8255
        v5186[1][v5239] = v5237;	// L8256
        int32_t v5240 = k10[1];	// L8257
        ac_int<33, true> v5241 = v5240;	// L8258
        ac_int<33, true> v5242 = v5241 + 1;	// L8259
        int32_t v5243 = v5242;	// L8260
        k10[1] = v5243;	// L8261
      }
    }
    int32_t v5244 = cret2[1];	// L8264
    v5188.write(v5244);	// L8265
  }
}

void col_s_0(
  half v5245[2][10],
  ac_channel< int32_t >& v5246,
  ac_channel< int32_t >& v5247,
  ac_channel< ac_int<17, false> >& v5248,
  ac_channel< ac_int<17, false> >& v5249
) {	// L8269
  int32_t k11[2];	// L8278
  for (int v5251 = 0; v5251 < 2; v5251++) {	// L8279
    k11[v5251] = 0;	// L8279
  }
  int32_t cret3[2];	// L8280
  for (int v5253 = 0; v5253 < 2; v5253++) {	// L8281
    cret3[v5253] = 0;	// L8281
  }
  int32_t zc3;	// L8282
  zc3 = 0;	// L8283
  int32_t v5255 = zc3;	// L8284
  v5246.write(v5255);	// L8285
  int32_t v5256 = zc3;	// L8286
  v5247.write(v5256);	// L8287
  int32_t v5257 = zc3;	// L8288
  v5246.write(v5257);	// L8289
  int32_t v5258 = zc3;	// L8290
  v5247.write(v5258);	// L8291
  int32_t v5259 = zc3;	// L8292
  v5246.write(v5259);	// L8293
  int32_t v5260 = zc3;	// L8294
  v5247.write(v5260);	// L8295
  int32_t v5261 = zc3;	// L8296
  v5246.write(v5261);	// L8297
  int32_t v5262 = zc3;	// L8298
  v5247.write(v5262);	// L8299
  int32_t v5263 = zc3;	// L8300
  v5246.write(v5263);	// L8301
  int32_t v5264 = zc3;	// L8302
  v5247.write(v5264);	// L8303
  cret3[0] = 2;	// L8304
  int32_t v5265 = cret3[0];	// L8305
  v5246.write(v5265);	// L8306
  cret3[1] = 2;	// L8307
  int32_t v5266 = cret3[1];	// L8308
  v5247.write(v5266);	// L8309
  l_S_t_0_t11: for (int t11 = 0; t11 < 10; t11++) {	// L8310
    ac_int<17, false> v5268 = v5248.read();	// L8311
    ac_int<17, false> w14;	// L8312
    w14 = v5268;	// L8313
    cret3[0] = 0;	// L8314
    ac_int<17, true> v5270 = w14;	// L8315
    bool v5271;
    ap_int<17> v5271_tmp = v5270;
    v5271 = v5271_tmp[0];	// L8316
    int32_t v5272 = v5271;	// L8317
    bool v5273 = v5272 == 1;	// L8318
    if (v5273) {	// L8319
      cret3[0] = 1;	// L8320
      int32_t v5274 = k11[0];	// L8321
      bool v5275 = v5274 < 10;	// L8322
      if (v5275) {	// L8323
        ac_int<17, true> v5276 = w14;	// L8324
        int16_t v5277;
        ap_int<17> v5277_tmp = v5276;
        v5277 = v5277_tmp(16, 1);	// L8325
        half v5278;
        union { uint16_t from; half to;} _converter_v5277_to_v5278 = {};
        _converter_v5277_to_v5278.from = v5277;
        v5278 = _converter_v5277_to_v5278.to;	// L8326
        int32_t v5279 = k11[0];	// L8327
        int v5280 = v5279;	// L8328
        v5245[0][v5280] = v5278;	// L8329
        int32_t v5281 = k11[0];	// L8330
        ac_int<33, true> v5282 = v5281;	// L8331
        ac_int<33, true> v5283 = v5282 + 1;	// L8332
        int32_t v5284 = v5283;	// L8333
        k11[0] = v5284;	// L8334
      }
    }
    int32_t v5285 = cret3[0];	// L8337
    v5246.write(v5285);	// L8338
    ac_int<17, false> v5286 = v5249.read();	// L8339
    ac_int<17, false> w15;	// L8340
    w15 = v5286;	// L8341
    cret3[1] = 0;	// L8342
    ac_int<17, true> v5288 = w15;	// L8343
    bool v5289;
    ap_int<17> v5289_tmp = v5288;
    v5289 = v5289_tmp[0];	// L8344
    int32_t v5290 = v5289;	// L8345
    bool v5291 = v5290 == 1;	// L8346
    if (v5291) {	// L8347
      cret3[1] = 1;	// L8348
      int32_t v5292 = k11[1];	// L8349
      bool v5293 = v5292 < 10;	// L8350
      if (v5293) {	// L8351
        ac_int<17, true> v5294 = w15;	// L8352
        int16_t v5295;
        ap_int<17> v5295_tmp = v5294;
        v5295 = v5295_tmp(16, 1);	// L8353
        half v5296;
        union { uint16_t from; half to;} _converter_v5295_to_v5296 = {};
        _converter_v5295_to_v5296.from = v5295;
        v5296 = _converter_v5295_to_v5296.to;	// L8354
        int32_t v5297 = k11[1];	// L8355
        int v5298 = v5297;	// L8356
        v5245[1][v5298] = v5296;	// L8357
        int32_t v5299 = k11[1];	// L8358
        ac_int<33, true> v5300 = v5299;	// L8359
        ac_int<33, true> v5301 = v5300 + 1;	// L8360
        int32_t v5302 = v5301;	// L8361
        k11[1] = v5302;	// L8362
      }
    }
    int32_t v5303 = cret3[1];	// L8365
    v5247.write(v5303);	// L8366
  }
}

void rdrv_w_0(
  int32_t v5304[2][10],
  ac_channel< ac_int<26, false> >& v5305,
  ac_channel< ac_int<26, false> >& v5306,
  ac_channel< int32_t >& v5307,
  ac_channel< int32_t >& v5308
) {	// L8370
  int32_t dcred4[2];	// L8378
  for (int v5310 = 0; v5310 < 2; v5310++) {	// L8379
    dcred4[v5310] = 0;	// L8379
  }
  int32_t sp4[2];	// L8380
  for (int v5312 = 0; v5312 < 2; v5312++) {	// L8381
    sp4[v5312] = 0;	// L8381
  }
  ac_int<26, false> zp;	// L8382
  zp = 0;	// L8383
  ac_int<26, true> v5314 = zp;	// L8384
  v5305.write(v5314);	// L8385
  ac_int<26, true> v5315 = zp;	// L8386
  v5306.write(v5315);	// L8387
  ac_int<26, true> v5316 = zp;	// L8388
  v5305.write(v5316);	// L8389
  ac_int<26, true> v5317 = zp;	// L8390
  v5306.write(v5317);	// L8391
  ac_int<26, true> v5318 = zp;	// L8392
  v5305.write(v5318);	// L8393
  ac_int<26, true> v5319 = zp;	// L8394
  v5306.write(v5319);	// L8395
  ac_int<26, true> v5320 = zp;	// L8396
  v5305.write(v5320);	// L8397
  ac_int<26, true> v5321 = zp;	// L8398
  v5306.write(v5321);	// L8399
  ac_int<26, true> v5322 = zp;	// L8400
  v5305.write(v5322);	// L8401
  ac_int<26, true> v5323 = zp;	// L8402
  v5306.write(v5323);	// L8403
  l_S_t_0_t12: for (int t12 = 0; t12 < 10; t12++) {	// L8404
    int32_t v5325 = v5307.read();	// L8405
    int32_t v5326 = dcred4[0];	// L8406
    ac_int<33, true> v5327 = v5326;	// L8407
    ac_int<33, true> v5328 = v5325;	// L8408
    ac_int<33, true> v5329 = v5327 + v5328;	// L8409
    int32_t v5330 = v5329;	// L8410
    dcred4[0] = v5330;	// L8411
    ac_int<26, false> pw;	// L8412
    pw = 0;	// L8413
    int32_t v5332 = sp4[0];	// L8414
    bool v5333 = v5332 < 10;	// L8415
    if (v5333) {	// L8416
      ac_int<26, false> cand;	// L8417
      cand = 0;	// L8418
      int32_t v5335 = sp4[0];	// L8419
      int v5336 = v5335;	// L8420
      int32_t v5337 = v5304[0][v5336];	// L8421
      ac_int<26, false> v5338 = v5337;	// L8422
      ac_int<26, true> v5339 = cand;	// L8423
      ac_int<26, true> v5340;
      ap_int<26> v5340_tmp = v5339;
      v5340_tmp(25, 0) = v5338;
      v5340 = v5340_tmp;	// L8424
      cand = v5340;	// L8425
      ac_int<26, true> v5341 = cand;	// L8426
      bool v5342;
      ap_int<26> v5342_tmp = v5341;
      v5342 = v5342_tmp[25];	// L8427
      int32_t v5343 = v5342;	// L8428
      bool v5344 = v5343 == 0;	// L8429
      if (v5344) {	// L8430
        int32_t v5345 = sp4[0];	// L8431
        ac_int<33, true> v5346 = v5345;	// L8432
        ac_int<33, true> v5347 = v5346 + 1;	// L8433
        int32_t v5348 = v5347;	// L8434
        sp4[0] = v5348;	// L8435
      } else {
        int32_t v5349 = dcred4[0];	// L8437
        bool v5350 = v5349 > 0;	// L8438
        if (v5350) {	// L8439
          ac_int<26, true> v5351 = cand;	// L8440
          pw = v5351;	// L8441
          int32_t v5352 = dcred4[0];	// L8442
          ac_int<33, true> v5353 = v5352;	// L8443
          ac_int<33, true> v5354 = v5353 - 1;	// L8444
          int32_t v5355 = v5354;	// L8445
          dcred4[0] = v5355;	// L8446
          int32_t v5356 = sp4[0];	// L8447
          ac_int<33, true> v5357 = v5356;	// L8448
          ac_int<33, true> v5358 = v5357 + 1;	// L8449
          int32_t v5359 = v5358;	// L8450
          sp4[0] = v5359;	// L8451
        }
      }
    }
    ac_int<26, true> v5360 = pw;	// L8455
    v5305.write(v5360);	// L8456
    int32_t v5361 = v5308.read();	// L8457
    int32_t v5362 = dcred4[1];	// L8458
    ac_int<33, true> v5363 = v5362;	// L8459
    ac_int<33, true> v5364 = v5361;	// L8460
    ac_int<33, true> v5365 = v5363 + v5364;	// L8461
    int32_t v5366 = v5365;	// L8462
    dcred4[1] = v5366;	// L8463
    ac_int<26, false> pw1;	// L8464
    pw1 = 0;	// L8465
    int32_t v5368 = sp4[1];	// L8466
    bool v5369 = v5368 < 10;	// L8467
    if (v5369) {	// L8468
      ac_int<26, false> cand1;	// L8469
      cand1 = 0;	// L8470
      int32_t v5371 = sp4[1];	// L8471
      int v5372 = v5371;	// L8472
      int32_t v5373 = v5304[1][v5372];	// L8473
      ac_int<26, false> v5374 = v5373;	// L8474
      ac_int<26, true> v5375 = cand1;	// L8475
      ac_int<26, true> v5376;
      ap_int<26> v5376_tmp = v5375;
      v5376_tmp(25, 0) = v5374;
      v5376 = v5376_tmp;	// L8476
      cand1 = v5376;	// L8477
      ac_int<26, true> v5377 = cand1;	// L8478
      bool v5378;
      ap_int<26> v5378_tmp = v5377;
      v5378 = v5378_tmp[25];	// L8479
      int32_t v5379 = v5378;	// L8480
      bool v5380 = v5379 == 0;	// L8481
      if (v5380) {	// L8482
        int32_t v5381 = sp4[1];	// L8483
        ac_int<33, true> v5382 = v5381;	// L8484
        ac_int<33, true> v5383 = v5382 + 1;	// L8485
        int32_t v5384 = v5383;	// L8486
        sp4[1] = v5384;	// L8487
      } else {
        int32_t v5385 = dcred4[1];	// L8489
        bool v5386 = v5385 > 0;	// L8490
        if (v5386) {	// L8491
          ac_int<26, true> v5387 = cand1;	// L8492
          pw1 = v5387;	// L8493
          int32_t v5388 = dcred4[1];	// L8494
          ac_int<33, true> v5389 = v5388;	// L8495
          ac_int<33, true> v5390 = v5389 - 1;	// L8496
          int32_t v5391 = v5390;	// L8497
          dcred4[1] = v5391;	// L8498
          int32_t v5392 = sp4[1];	// L8499
          ac_int<33, true> v5393 = v5392;	// L8500
          ac_int<33, true> v5394 = v5393 + 1;	// L8501
          int32_t v5395 = v5394;	// L8502
          sp4[1] = v5395;	// L8503
        }
      }
    }
    ac_int<26, true> v5396 = pw1;	// L8507
    v5306.write(v5396);	// L8508
  }
}

void rdrv_e_0(
  int32_t v5397[2][10],
  ac_channel< ac_int<26, false> >& v5398,
  ac_channel< ac_int<26, false> >& v5399,
  ac_channel< int32_t >& v5400,
  ac_channel< int32_t >& v5401
) {	// L8512
  int32_t dcred5[2];	// L8520
  for (int v5403 = 0; v5403 < 2; v5403++) {	// L8521
    dcred5[v5403] = 0;	// L8521
  }
  int32_t sp5[2];	// L8522
  for (int v5405 = 0; v5405 < 2; v5405++) {	// L8523
    sp5[v5405] = 0;	// L8523
  }
  ac_int<26, false> zp1;	// L8524
  zp1 = 0;	// L8525
  ac_int<26, true> v5407 = zp1;	// L8526
  v5398.write(v5407);	// L8527
  ac_int<26, true> v5408 = zp1;	// L8528
  v5399.write(v5408);	// L8529
  ac_int<26, true> v5409 = zp1;	// L8530
  v5398.write(v5409);	// L8531
  ac_int<26, true> v5410 = zp1;	// L8532
  v5399.write(v5410);	// L8533
  ac_int<26, true> v5411 = zp1;	// L8534
  v5398.write(v5411);	// L8535
  ac_int<26, true> v5412 = zp1;	// L8536
  v5399.write(v5412);	// L8537
  ac_int<26, true> v5413 = zp1;	// L8538
  v5398.write(v5413);	// L8539
  ac_int<26, true> v5414 = zp1;	// L8540
  v5399.write(v5414);	// L8541
  ac_int<26, true> v5415 = zp1;	// L8542
  v5398.write(v5415);	// L8543
  ac_int<26, true> v5416 = zp1;	// L8544
  v5399.write(v5416);	// L8545
  l_S_t_0_t13: for (int t13 = 0; t13 < 10; t13++) {	// L8546
    int32_t v5418 = v5400.read();	// L8547
    int32_t v5419 = dcred5[0];	// L8548
    ac_int<33, true> v5420 = v5419;	// L8549
    ac_int<33, true> v5421 = v5418;	// L8550
    ac_int<33, true> v5422 = v5420 + v5421;	// L8551
    int32_t v5423 = v5422;	// L8552
    dcred5[0] = v5423;	// L8553
    ac_int<26, false> pw2;	// L8554
    pw2 = 0;	// L8555
    int32_t v5425 = sp5[0];	// L8556
    bool v5426 = v5425 < 10;	// L8557
    if (v5426) {	// L8558
      ac_int<26, false> cand2;	// L8559
      cand2 = 0;	// L8560
      int32_t v5428 = sp5[0];	// L8561
      int v5429 = v5428;	// L8562
      int32_t v5430 = v5397[0][v5429];	// L8563
      ac_int<26, false> v5431 = v5430;	// L8564
      ac_int<26, true> v5432 = cand2;	// L8565
      ac_int<26, true> v5433;
      ap_int<26> v5433_tmp = v5432;
      v5433_tmp(25, 0) = v5431;
      v5433 = v5433_tmp;	// L8566
      cand2 = v5433;	// L8567
      ac_int<26, true> v5434 = cand2;	// L8568
      bool v5435;
      ap_int<26> v5435_tmp = v5434;
      v5435 = v5435_tmp[25];	// L8569
      int32_t v5436 = v5435;	// L8570
      bool v5437 = v5436 == 0;	// L8571
      if (v5437) {	// L8572
        int32_t v5438 = sp5[0];	// L8573
        ac_int<33, true> v5439 = v5438;	// L8574
        ac_int<33, true> v5440 = v5439 + 1;	// L8575
        int32_t v5441 = v5440;	// L8576
        sp5[0] = v5441;	// L8577
      } else {
        int32_t v5442 = dcred5[0];	// L8579
        bool v5443 = v5442 > 0;	// L8580
        if (v5443) {	// L8581
          ac_int<26, true> v5444 = cand2;	// L8582
          pw2 = v5444;	// L8583
          int32_t v5445 = dcred5[0];	// L8584
          ac_int<33, true> v5446 = v5445;	// L8585
          ac_int<33, true> v5447 = v5446 - 1;	// L8586
          int32_t v5448 = v5447;	// L8587
          dcred5[0] = v5448;	// L8588
          int32_t v5449 = sp5[0];	// L8589
          ac_int<33, true> v5450 = v5449;	// L8590
          ac_int<33, true> v5451 = v5450 + 1;	// L8591
          int32_t v5452 = v5451;	// L8592
          sp5[0] = v5452;	// L8593
        }
      }
    }
    ac_int<26, true> v5453 = pw2;	// L8597
    v5398.write(v5453);	// L8598
    int32_t v5454 = v5401.read();	// L8599
    int32_t v5455 = dcred5[1];	// L8600
    ac_int<33, true> v5456 = v5455;	// L8601
    ac_int<33, true> v5457 = v5454;	// L8602
    ac_int<33, true> v5458 = v5456 + v5457;	// L8603
    int32_t v5459 = v5458;	// L8604
    dcred5[1] = v5459;	// L8605
    ac_int<26, false> pw3;	// L8606
    pw3 = 0;	// L8607
    int32_t v5461 = sp5[1];	// L8608
    bool v5462 = v5461 < 10;	// L8609
    if (v5462) {	// L8610
      ac_int<26, false> cand3;	// L8611
      cand3 = 0;	// L8612
      int32_t v5464 = sp5[1];	// L8613
      int v5465 = v5464;	// L8614
      int32_t v5466 = v5397[1][v5465];	// L8615
      ac_int<26, false> v5467 = v5466;	// L8616
      ac_int<26, true> v5468 = cand3;	// L8617
      ac_int<26, true> v5469;
      ap_int<26> v5469_tmp = v5468;
      v5469_tmp(25, 0) = v5467;
      v5469 = v5469_tmp;	// L8618
      cand3 = v5469;	// L8619
      ac_int<26, true> v5470 = cand3;	// L8620
      bool v5471;
      ap_int<26> v5471_tmp = v5470;
      v5471 = v5471_tmp[25];	// L8621
      int32_t v5472 = v5471;	// L8622
      bool v5473 = v5472 == 0;	// L8623
      if (v5473) {	// L8624
        int32_t v5474 = sp5[1];	// L8625
        ac_int<33, true> v5475 = v5474;	// L8626
        ac_int<33, true> v5476 = v5475 + 1;	// L8627
        int32_t v5477 = v5476;	// L8628
        sp5[1] = v5477;	// L8629
      } else {
        int32_t v5478 = dcred5[1];	// L8631
        bool v5479 = v5478 > 0;	// L8632
        if (v5479) {	// L8633
          ac_int<26, true> v5480 = cand3;	// L8634
          pw3 = v5480;	// L8635
          int32_t v5481 = dcred5[1];	// L8636
          ac_int<33, true> v5482 = v5481;	// L8637
          ac_int<33, true> v5483 = v5482 - 1;	// L8638
          int32_t v5484 = v5483;	// L8639
          dcred5[1] = v5484;	// L8640
          int32_t v5485 = sp5[1];	// L8641
          ac_int<33, true> v5486 = v5485;	// L8642
          ac_int<33, true> v5487 = v5486 + 1;	// L8643
          int32_t v5488 = v5487;	// L8644
          sp5[1] = v5488;	// L8645
        }
      }
    }
    ac_int<26, true> v5489 = pw3;	// L8649
    v5399.write(v5489);	// L8650
  }
}

void rdrv_n_0(
  int32_t v5490[2][10],
  ac_channel< ac_int<26, false> >& v5491,
  ac_channel< ac_int<26, false> >& v5492,
  ac_channel< int32_t >& v5493,
  ac_channel< int32_t >& v5494
) {	// L8654
  int32_t dcred6[2];	// L8662
  for (int v5496 = 0; v5496 < 2; v5496++) {	// L8663
    dcred6[v5496] = 0;	// L8663
  }
  int32_t sp6[2];	// L8664
  for (int v5498 = 0; v5498 < 2; v5498++) {	// L8665
    sp6[v5498] = 0;	// L8665
  }
  ac_int<26, false> zp2;	// L8666
  zp2 = 0;	// L8667
  ac_int<26, true> v5500 = zp2;	// L8668
  v5491.write(v5500);	// L8669
  ac_int<26, true> v5501 = zp2;	// L8670
  v5492.write(v5501);	// L8671
  ac_int<26, true> v5502 = zp2;	// L8672
  v5491.write(v5502);	// L8673
  ac_int<26, true> v5503 = zp2;	// L8674
  v5492.write(v5503);	// L8675
  ac_int<26, true> v5504 = zp2;	// L8676
  v5491.write(v5504);	// L8677
  ac_int<26, true> v5505 = zp2;	// L8678
  v5492.write(v5505);	// L8679
  ac_int<26, true> v5506 = zp2;	// L8680
  v5491.write(v5506);	// L8681
  ac_int<26, true> v5507 = zp2;	// L8682
  v5492.write(v5507);	// L8683
  ac_int<26, true> v5508 = zp2;	// L8684
  v5491.write(v5508);	// L8685
  ac_int<26, true> v5509 = zp2;	// L8686
  v5492.write(v5509);	// L8687
  l_S_t_0_t14: for (int t14 = 0; t14 < 10; t14++) {	// L8688
    int32_t v5511 = v5493.read();	// L8689
    int32_t v5512 = dcred6[0];	// L8690
    ac_int<33, true> v5513 = v5512;	// L8691
    ac_int<33, true> v5514 = v5511;	// L8692
    ac_int<33, true> v5515 = v5513 + v5514;	// L8693
    int32_t v5516 = v5515;	// L8694
    dcred6[0] = v5516;	// L8695
    ac_int<26, false> pw4;	// L8696
    pw4 = 0;	// L8697
    int32_t v5518 = sp6[0];	// L8698
    bool v5519 = v5518 < 10;	// L8699
    if (v5519) {	// L8700
      ac_int<26, false> cand4;	// L8701
      cand4 = 0;	// L8702
      int32_t v5521 = sp6[0];	// L8703
      int v5522 = v5521;	// L8704
      int32_t v5523 = v5490[0][v5522];	// L8705
      ac_int<26, false> v5524 = v5523;	// L8706
      ac_int<26, true> v5525 = cand4;	// L8707
      ac_int<26, true> v5526;
      ap_int<26> v5526_tmp = v5525;
      v5526_tmp(25, 0) = v5524;
      v5526 = v5526_tmp;	// L8708
      cand4 = v5526;	// L8709
      ac_int<26, true> v5527 = cand4;	// L8710
      bool v5528;
      ap_int<26> v5528_tmp = v5527;
      v5528 = v5528_tmp[25];	// L8711
      int32_t v5529 = v5528;	// L8712
      bool v5530 = v5529 == 0;	// L8713
      if (v5530) {	// L8714
        int32_t v5531 = sp6[0];	// L8715
        ac_int<33, true> v5532 = v5531;	// L8716
        ac_int<33, true> v5533 = v5532 + 1;	// L8717
        int32_t v5534 = v5533;	// L8718
        sp6[0] = v5534;	// L8719
      } else {
        int32_t v5535 = dcred6[0];	// L8721
        bool v5536 = v5535 > 0;	// L8722
        if (v5536) {	// L8723
          ac_int<26, true> v5537 = cand4;	// L8724
          pw4 = v5537;	// L8725
          int32_t v5538 = dcred6[0];	// L8726
          ac_int<33, true> v5539 = v5538;	// L8727
          ac_int<33, true> v5540 = v5539 - 1;	// L8728
          int32_t v5541 = v5540;	// L8729
          dcred6[0] = v5541;	// L8730
          int32_t v5542 = sp6[0];	// L8731
          ac_int<33, true> v5543 = v5542;	// L8732
          ac_int<33, true> v5544 = v5543 + 1;	// L8733
          int32_t v5545 = v5544;	// L8734
          sp6[0] = v5545;	// L8735
        }
      }
    }
    ac_int<26, true> v5546 = pw4;	// L8739
    v5491.write(v5546);	// L8740
    int32_t v5547 = v5494.read();	// L8741
    int32_t v5548 = dcred6[1];	// L8742
    ac_int<33, true> v5549 = v5548;	// L8743
    ac_int<33, true> v5550 = v5547;	// L8744
    ac_int<33, true> v5551 = v5549 + v5550;	// L8745
    int32_t v5552 = v5551;	// L8746
    dcred6[1] = v5552;	// L8747
    ac_int<26, false> pw5;	// L8748
    pw5 = 0;	// L8749
    int32_t v5554 = sp6[1];	// L8750
    bool v5555 = v5554 < 10;	// L8751
    if (v5555) {	// L8752
      ac_int<26, false> cand5;	// L8753
      cand5 = 0;	// L8754
      int32_t v5557 = sp6[1];	// L8755
      int v5558 = v5557;	// L8756
      int32_t v5559 = v5490[1][v5558];	// L8757
      ac_int<26, false> v5560 = v5559;	// L8758
      ac_int<26, true> v5561 = cand5;	// L8759
      ac_int<26, true> v5562;
      ap_int<26> v5562_tmp = v5561;
      v5562_tmp(25, 0) = v5560;
      v5562 = v5562_tmp;	// L8760
      cand5 = v5562;	// L8761
      ac_int<26, true> v5563 = cand5;	// L8762
      bool v5564;
      ap_int<26> v5564_tmp = v5563;
      v5564 = v5564_tmp[25];	// L8763
      int32_t v5565 = v5564;	// L8764
      bool v5566 = v5565 == 0;	// L8765
      if (v5566) {	// L8766
        int32_t v5567 = sp6[1];	// L8767
        ac_int<33, true> v5568 = v5567;	// L8768
        ac_int<33, true> v5569 = v5568 + 1;	// L8769
        int32_t v5570 = v5569;	// L8770
        sp6[1] = v5570;	// L8771
      } else {
        int32_t v5571 = dcred6[1];	// L8773
        bool v5572 = v5571 > 0;	// L8774
        if (v5572) {	// L8775
          ac_int<26, true> v5573 = cand5;	// L8776
          pw5 = v5573;	// L8777
          int32_t v5574 = dcred6[1];	// L8778
          ac_int<33, true> v5575 = v5574;	// L8779
          ac_int<33, true> v5576 = v5575 - 1;	// L8780
          int32_t v5577 = v5576;	// L8781
          dcred6[1] = v5577;	// L8782
          int32_t v5578 = sp6[1];	// L8783
          ac_int<33, true> v5579 = v5578;	// L8784
          ac_int<33, true> v5580 = v5579 + 1;	// L8785
          int32_t v5581 = v5580;	// L8786
          sp6[1] = v5581;	// L8787
        }
      }
    }
    ac_int<26, true> v5582 = pw5;	// L8791
    v5492.write(v5582);	// L8792
  }
}

void rdrv_s_0(
  int32_t v5583[2][10],
  ac_channel< ac_int<26, false> >& v5584,
  ac_channel< ac_int<26, false> >& v5585,
  ac_channel< int32_t >& v5586,
  ac_channel< int32_t >& v5587
) {	// L8796
  int32_t dcred7[2];	// L8804
  for (int v5589 = 0; v5589 < 2; v5589++) {	// L8805
    dcred7[v5589] = 0;	// L8805
  }
  int32_t sp7[2];	// L8806
  for (int v5591 = 0; v5591 < 2; v5591++) {	// L8807
    sp7[v5591] = 0;	// L8807
  }
  ac_int<26, false> zp3;	// L8808
  zp3 = 0;	// L8809
  ac_int<26, true> v5593 = zp3;	// L8810
  v5584.write(v5593);	// L8811
  ac_int<26, true> v5594 = zp3;	// L8812
  v5585.write(v5594);	// L8813
  ac_int<26, true> v5595 = zp3;	// L8814
  v5584.write(v5595);	// L8815
  ac_int<26, true> v5596 = zp3;	// L8816
  v5585.write(v5596);	// L8817
  ac_int<26, true> v5597 = zp3;	// L8818
  v5584.write(v5597);	// L8819
  ac_int<26, true> v5598 = zp3;	// L8820
  v5585.write(v5598);	// L8821
  ac_int<26, true> v5599 = zp3;	// L8822
  v5584.write(v5599);	// L8823
  ac_int<26, true> v5600 = zp3;	// L8824
  v5585.write(v5600);	// L8825
  ac_int<26, true> v5601 = zp3;	// L8826
  v5584.write(v5601);	// L8827
  ac_int<26, true> v5602 = zp3;	// L8828
  v5585.write(v5602);	// L8829
  l_S_t_0_t15: for (int t15 = 0; t15 < 10; t15++) {	// L8830
    int32_t v5604 = v5586.read();	// L8831
    int32_t v5605 = dcred7[0];	// L8832
    ac_int<33, true> v5606 = v5605;	// L8833
    ac_int<33, true> v5607 = v5604;	// L8834
    ac_int<33, true> v5608 = v5606 + v5607;	// L8835
    int32_t v5609 = v5608;	// L8836
    dcred7[0] = v5609;	// L8837
    ac_int<26, false> pw6;	// L8838
    pw6 = 0;	// L8839
    int32_t v5611 = sp7[0];	// L8840
    bool v5612 = v5611 < 10;	// L8841
    if (v5612) {	// L8842
      ac_int<26, false> cand6;	// L8843
      cand6 = 0;	// L8844
      int32_t v5614 = sp7[0];	// L8845
      int v5615 = v5614;	// L8846
      int32_t v5616 = v5583[0][v5615];	// L8847
      ac_int<26, false> v5617 = v5616;	// L8848
      ac_int<26, true> v5618 = cand6;	// L8849
      ac_int<26, true> v5619;
      ap_int<26> v5619_tmp = v5618;
      v5619_tmp(25, 0) = v5617;
      v5619 = v5619_tmp;	// L8850
      cand6 = v5619;	// L8851
      ac_int<26, true> v5620 = cand6;	// L8852
      bool v5621;
      ap_int<26> v5621_tmp = v5620;
      v5621 = v5621_tmp[25];	// L8853
      int32_t v5622 = v5621;	// L8854
      bool v5623 = v5622 == 0;	// L8855
      if (v5623) {	// L8856
        int32_t v5624 = sp7[0];	// L8857
        ac_int<33, true> v5625 = v5624;	// L8858
        ac_int<33, true> v5626 = v5625 + 1;	// L8859
        int32_t v5627 = v5626;	// L8860
        sp7[0] = v5627;	// L8861
      } else {
        int32_t v5628 = dcred7[0];	// L8863
        bool v5629 = v5628 > 0;	// L8864
        if (v5629) {	// L8865
          ac_int<26, true> v5630 = cand6;	// L8866
          pw6 = v5630;	// L8867
          int32_t v5631 = dcred7[0];	// L8868
          ac_int<33, true> v5632 = v5631;	// L8869
          ac_int<33, true> v5633 = v5632 - 1;	// L8870
          int32_t v5634 = v5633;	// L8871
          dcred7[0] = v5634;	// L8872
          int32_t v5635 = sp7[0];	// L8873
          ac_int<33, true> v5636 = v5635;	// L8874
          ac_int<33, true> v5637 = v5636 + 1;	// L8875
          int32_t v5638 = v5637;	// L8876
          sp7[0] = v5638;	// L8877
        }
      }
    }
    ac_int<26, true> v5639 = pw6;	// L8881
    v5584.write(v5639);	// L8882
    int32_t v5640 = v5587.read();	// L8883
    int32_t v5641 = dcred7[1];	// L8884
    ac_int<33, true> v5642 = v5641;	// L8885
    ac_int<33, true> v5643 = v5640;	// L8886
    ac_int<33, true> v5644 = v5642 + v5643;	// L8887
    int32_t v5645 = v5644;	// L8888
    dcred7[1] = v5645;	// L8889
    ac_int<26, false> pw7;	// L8890
    pw7 = 0;	// L8891
    int32_t v5647 = sp7[1];	// L8892
    bool v5648 = v5647 < 10;	// L8893
    if (v5648) {	// L8894
      ac_int<26, false> cand7;	// L8895
      cand7 = 0;	// L8896
      int32_t v5650 = sp7[1];	// L8897
      int v5651 = v5650;	// L8898
      int32_t v5652 = v5583[1][v5651];	// L8899
      ac_int<26, false> v5653 = v5652;	// L8900
      ac_int<26, true> v5654 = cand7;	// L8901
      ac_int<26, true> v5655;
      ap_int<26> v5655_tmp = v5654;
      v5655_tmp(25, 0) = v5653;
      v5655 = v5655_tmp;	// L8902
      cand7 = v5655;	// L8903
      ac_int<26, true> v5656 = cand7;	// L8904
      bool v5657;
      ap_int<26> v5657_tmp = v5656;
      v5657 = v5657_tmp[25];	// L8905
      int32_t v5658 = v5657;	// L8906
      bool v5659 = v5658 == 0;	// L8907
      if (v5659) {	// L8908
        int32_t v5660 = sp7[1];	// L8909
        ac_int<33, true> v5661 = v5660;	// L8910
        ac_int<33, true> v5662 = v5661 + 1;	// L8911
        int32_t v5663 = v5662;	// L8912
        sp7[1] = v5663;	// L8913
      } else {
        int32_t v5664 = dcred7[1];	// L8915
        bool v5665 = v5664 > 0;	// L8916
        if (v5665) {	// L8917
          ac_int<26, true> v5666 = cand7;	// L8918
          pw7 = v5666;	// L8919
          int32_t v5667 = dcred7[1];	// L8920
          ac_int<33, true> v5668 = v5667;	// L8921
          ac_int<33, true> v5669 = v5668 - 1;	// L8922
          int32_t v5670 = v5669;	// L8923
          dcred7[1] = v5670;	// L8924
          int32_t v5671 = sp7[1];	// L8925
          ac_int<33, true> v5672 = v5671;	// L8926
          ac_int<33, true> v5673 = v5672 + 1;	// L8927
          int32_t v5674 = v5673;	// L8928
          sp7[1] = v5674;	// L8929
        }
      }
    }
    ac_int<26, true> v5675 = pw7;	// L8933
    v5585.write(v5675);	// L8934
  }
}

void rclc_w_0(
  int32_t v5676[2][10],
  ac_channel< int32_t >& v5677,
  ac_channel< int32_t >& v5678,
  ac_channel< ac_int<26, false> >& v5679,
  ac_channel< ac_int<26, false> >& v5680
) {	// L8938
  int32_t k12[2];	// L8948
  for (int v5682 = 0; v5682 < 2; v5682++) {	// L8949
    k12[v5682] = 0;	// L8949
  }
  int32_t cret4[2];	// L8950
  for (int v5684 = 0; v5684 < 2; v5684++) {	// L8951
    cret4[v5684] = 0;	// L8951
  }
  int32_t zc4;	// L8952
  zc4 = 0;	// L8953
  int32_t v5686 = zc4;	// L8954
  v5677.write(v5686);	// L8955
  int32_t v5687 = zc4;	// L8956
  v5678.write(v5687);	// L8957
  int32_t v5688 = zc4;	// L8958
  v5677.write(v5688);	// L8959
  int32_t v5689 = zc4;	// L8960
  v5678.write(v5689);	// L8961
  int32_t v5690 = zc4;	// L8962
  v5677.write(v5690);	// L8963
  int32_t v5691 = zc4;	// L8964
  v5678.write(v5691);	// L8965
  int32_t v5692 = zc4;	// L8966
  v5677.write(v5692);	// L8967
  int32_t v5693 = zc4;	// L8968
  v5678.write(v5693);	// L8969
  int32_t v5694 = zc4;	// L8970
  v5677.write(v5694);	// L8971
  int32_t v5695 = zc4;	// L8972
  v5678.write(v5695);	// L8973
  cret4[0] = 2;	// L8974
  int32_t v5696 = cret4[0];	// L8975
  v5677.write(v5696);	// L8976
  cret4[1] = 2;	// L8977
  int32_t v5697 = cret4[1];	// L8978
  v5678.write(v5697);	// L8979
  l_S_t_0_t16: for (int t16 = 0; t16 < 10; t16++) {	// L8980
    ac_int<26, false> v5699 = v5679.read();	// L8981
    ac_int<26, false> pw8;	// L8982
    pw8 = v5699;	// L8983
    cret4[0] = 0;	// L8984
    ac_int<26, true> v5701 = pw8;	// L8985
    bool v5702;
    ap_int<26> v5702_tmp = v5701;
    v5702 = v5702_tmp[25];	// L8986
    int32_t v5703 = v5702;	// L8987
    bool v5704 = v5703 == 1;	// L8988
    if (v5704) {	// L8989
      cret4[0] = 1;	// L8990
      int32_t v5705 = k12[0];	// L8991
      bool v5706 = v5705 < 10;	// L8992
      if (v5706) {	// L8993
        ac_int<26, true> v5707 = pw8;	// L8994
        int32_t v5708 = v5707;	// L8995
        int32_t v5709 = v5708 & 67108863;	// L8996
        int32_t v5710 = k12[0];	// L8997
        int v5711 = v5710;	// L8998
        v5676[0][v5711] = v5709;	// L8999
        int32_t v5712 = k12[0];	// L9000
        ac_int<33, true> v5713 = v5712;	// L9001
        ac_int<33, true> v5714 = v5713 + 1;	// L9002
        int32_t v5715 = v5714;	// L9003
        k12[0] = v5715;	// L9004
      }
    }
    int32_t v5716 = cret4[0];	// L9007
    v5677.write(v5716);	// L9008
    ac_int<26, false> v5717 = v5680.read();	// L9009
    ac_int<26, false> pw9;	// L9010
    pw9 = v5717;	// L9011
    cret4[1] = 0;	// L9012
    ac_int<26, true> v5719 = pw9;	// L9013
    bool v5720;
    ap_int<26> v5720_tmp = v5719;
    v5720 = v5720_tmp[25];	// L9014
    int32_t v5721 = v5720;	// L9015
    bool v5722 = v5721 == 1;	// L9016
    if (v5722) {	// L9017
      cret4[1] = 1;	// L9018
      int32_t v5723 = k12[1];	// L9019
      bool v5724 = v5723 < 10;	// L9020
      if (v5724) {	// L9021
        ac_int<26, true> v5725 = pw9;	// L9022
        int32_t v5726 = v5725;	// L9023
        int32_t v5727 = v5726 & 67108863;	// L9024
        int32_t v5728 = k12[1];	// L9025
        int v5729 = v5728;	// L9026
        v5676[1][v5729] = v5727;	// L9027
        int32_t v5730 = k12[1];	// L9028
        ac_int<33, true> v5731 = v5730;	// L9029
        ac_int<33, true> v5732 = v5731 + 1;	// L9030
        int32_t v5733 = v5732;	// L9031
        k12[1] = v5733;	// L9032
      }
    }
    int32_t v5734 = cret4[1];	// L9035
    v5678.write(v5734);	// L9036
  }
}

void rclc_e_0(
  int32_t v5735[2][10],
  ac_channel< int32_t >& v5736,
  ac_channel< int32_t >& v5737,
  ac_channel< ac_int<26, false> >& v5738,
  ac_channel< ac_int<26, false> >& v5739
) {	// L9040
  int32_t k13[2];	// L9050
  for (int v5741 = 0; v5741 < 2; v5741++) {	// L9051
    k13[v5741] = 0;	// L9051
  }
  int32_t cret5[2];	// L9052
  for (int v5743 = 0; v5743 < 2; v5743++) {	// L9053
    cret5[v5743] = 0;	// L9053
  }
  int32_t zc5;	// L9054
  zc5 = 0;	// L9055
  int32_t v5745 = zc5;	// L9056
  v5736.write(v5745);	// L9057
  int32_t v5746 = zc5;	// L9058
  v5737.write(v5746);	// L9059
  int32_t v5747 = zc5;	// L9060
  v5736.write(v5747);	// L9061
  int32_t v5748 = zc5;	// L9062
  v5737.write(v5748);	// L9063
  int32_t v5749 = zc5;	// L9064
  v5736.write(v5749);	// L9065
  int32_t v5750 = zc5;	// L9066
  v5737.write(v5750);	// L9067
  int32_t v5751 = zc5;	// L9068
  v5736.write(v5751);	// L9069
  int32_t v5752 = zc5;	// L9070
  v5737.write(v5752);	// L9071
  int32_t v5753 = zc5;	// L9072
  v5736.write(v5753);	// L9073
  int32_t v5754 = zc5;	// L9074
  v5737.write(v5754);	// L9075
  cret5[0] = 2;	// L9076
  int32_t v5755 = cret5[0];	// L9077
  v5736.write(v5755);	// L9078
  cret5[1] = 2;	// L9079
  int32_t v5756 = cret5[1];	// L9080
  v5737.write(v5756);	// L9081
  l_S_t_0_t17: for (int t17 = 0; t17 < 10; t17++) {	// L9082
    ac_int<26, false> v5758 = v5738.read();	// L9083
    ac_int<26, false> pw10;	// L9084
    pw10 = v5758;	// L9085
    cret5[0] = 0;	// L9086
    ac_int<26, true> v5760 = pw10;	// L9087
    bool v5761;
    ap_int<26> v5761_tmp = v5760;
    v5761 = v5761_tmp[25];	// L9088
    int32_t v5762 = v5761;	// L9089
    bool v5763 = v5762 == 1;	// L9090
    if (v5763) {	// L9091
      cret5[0] = 1;	// L9092
      int32_t v5764 = k13[0];	// L9093
      bool v5765 = v5764 < 10;	// L9094
      if (v5765) {	// L9095
        ac_int<26, true> v5766 = pw10;	// L9096
        int32_t v5767 = v5766;	// L9097
        int32_t v5768 = v5767 & 67108863;	// L9098
        int32_t v5769 = k13[0];	// L9099
        int v5770 = v5769;	// L9100
        v5735[0][v5770] = v5768;	// L9101
        int32_t v5771 = k13[0];	// L9102
        ac_int<33, true> v5772 = v5771;	// L9103
        ac_int<33, true> v5773 = v5772 + 1;	// L9104
        int32_t v5774 = v5773;	// L9105
        k13[0] = v5774;	// L9106
      }
    }
    int32_t v5775 = cret5[0];	// L9109
    v5736.write(v5775);	// L9110
    ac_int<26, false> v5776 = v5739.read();	// L9111
    ac_int<26, false> pw11;	// L9112
    pw11 = v5776;	// L9113
    cret5[1] = 0;	// L9114
    ac_int<26, true> v5778 = pw11;	// L9115
    bool v5779;
    ap_int<26> v5779_tmp = v5778;
    v5779 = v5779_tmp[25];	// L9116
    int32_t v5780 = v5779;	// L9117
    bool v5781 = v5780 == 1;	// L9118
    if (v5781) {	// L9119
      cret5[1] = 1;	// L9120
      int32_t v5782 = k13[1];	// L9121
      bool v5783 = v5782 < 10;	// L9122
      if (v5783) {	// L9123
        ac_int<26, true> v5784 = pw11;	// L9124
        int32_t v5785 = v5784;	// L9125
        int32_t v5786 = v5785 & 67108863;	// L9126
        int32_t v5787 = k13[1];	// L9127
        int v5788 = v5787;	// L9128
        v5735[1][v5788] = v5786;	// L9129
        int32_t v5789 = k13[1];	// L9130
        ac_int<33, true> v5790 = v5789;	// L9131
        ac_int<33, true> v5791 = v5790 + 1;	// L9132
        int32_t v5792 = v5791;	// L9133
        k13[1] = v5792;	// L9134
      }
    }
    int32_t v5793 = cret5[1];	// L9137
    v5737.write(v5793);	// L9138
  }
}

void rclc_n_0(
  int32_t v5794[2][10],
  ac_channel< int32_t >& v5795,
  ac_channel< int32_t >& v5796,
  ac_channel< ac_int<26, false> >& v5797,
  ac_channel< ac_int<26, false> >& v5798
) {	// L9142
  int32_t k14[2];	// L9152
  for (int v5800 = 0; v5800 < 2; v5800++) {	// L9153
    k14[v5800] = 0;	// L9153
  }
  int32_t cret6[2];	// L9154
  for (int v5802 = 0; v5802 < 2; v5802++) {	// L9155
    cret6[v5802] = 0;	// L9155
  }
  int32_t zc6;	// L9156
  zc6 = 0;	// L9157
  int32_t v5804 = zc6;	// L9158
  v5795.write(v5804);	// L9159
  int32_t v5805 = zc6;	// L9160
  v5796.write(v5805);	// L9161
  int32_t v5806 = zc6;	// L9162
  v5795.write(v5806);	// L9163
  int32_t v5807 = zc6;	// L9164
  v5796.write(v5807);	// L9165
  int32_t v5808 = zc6;	// L9166
  v5795.write(v5808);	// L9167
  int32_t v5809 = zc6;	// L9168
  v5796.write(v5809);	// L9169
  int32_t v5810 = zc6;	// L9170
  v5795.write(v5810);	// L9171
  int32_t v5811 = zc6;	// L9172
  v5796.write(v5811);	// L9173
  int32_t v5812 = zc6;	// L9174
  v5795.write(v5812);	// L9175
  int32_t v5813 = zc6;	// L9176
  v5796.write(v5813);	// L9177
  cret6[0] = 2;	// L9178
  int32_t v5814 = cret6[0];	// L9179
  v5795.write(v5814);	// L9180
  cret6[1] = 2;	// L9181
  int32_t v5815 = cret6[1];	// L9182
  v5796.write(v5815);	// L9183
  l_S_t_0_t18: for (int t18 = 0; t18 < 10; t18++) {	// L9184
    ac_int<26, false> v5817 = v5797.read();	// L9185
    ac_int<26, false> pw12;	// L9186
    pw12 = v5817;	// L9187
    cret6[0] = 0;	// L9188
    ac_int<26, true> v5819 = pw12;	// L9189
    bool v5820;
    ap_int<26> v5820_tmp = v5819;
    v5820 = v5820_tmp[25];	// L9190
    int32_t v5821 = v5820;	// L9191
    bool v5822 = v5821 == 1;	// L9192
    if (v5822) {	// L9193
      cret6[0] = 1;	// L9194
      int32_t v5823 = k14[0];	// L9195
      bool v5824 = v5823 < 10;	// L9196
      if (v5824) {	// L9197
        ac_int<26, true> v5825 = pw12;	// L9198
        int32_t v5826 = v5825;	// L9199
        int32_t v5827 = v5826 & 67108863;	// L9200
        int32_t v5828 = k14[0];	// L9201
        int v5829 = v5828;	// L9202
        v5794[0][v5829] = v5827;	// L9203
        int32_t v5830 = k14[0];	// L9204
        ac_int<33, true> v5831 = v5830;	// L9205
        ac_int<33, true> v5832 = v5831 + 1;	// L9206
        int32_t v5833 = v5832;	// L9207
        k14[0] = v5833;	// L9208
      }
    }
    int32_t v5834 = cret6[0];	// L9211
    v5795.write(v5834);	// L9212
    ac_int<26, false> v5835 = v5798.read();	// L9213
    ac_int<26, false> pw13;	// L9214
    pw13 = v5835;	// L9215
    cret6[1] = 0;	// L9216
    ac_int<26, true> v5837 = pw13;	// L9217
    bool v5838;
    ap_int<26> v5838_tmp = v5837;
    v5838 = v5838_tmp[25];	// L9218
    int32_t v5839 = v5838;	// L9219
    bool v5840 = v5839 == 1;	// L9220
    if (v5840) {	// L9221
      cret6[1] = 1;	// L9222
      int32_t v5841 = k14[1];	// L9223
      bool v5842 = v5841 < 10;	// L9224
      if (v5842) {	// L9225
        ac_int<26, true> v5843 = pw13;	// L9226
        int32_t v5844 = v5843;	// L9227
        int32_t v5845 = v5844 & 67108863;	// L9228
        int32_t v5846 = k14[1];	// L9229
        int v5847 = v5846;	// L9230
        v5794[1][v5847] = v5845;	// L9231
        int32_t v5848 = k14[1];	// L9232
        ac_int<33, true> v5849 = v5848;	// L9233
        ac_int<33, true> v5850 = v5849 + 1;	// L9234
        int32_t v5851 = v5850;	// L9235
        k14[1] = v5851;	// L9236
      }
    }
    int32_t v5852 = cret6[1];	// L9239
    v5796.write(v5852);	// L9240
  }
}

void rclc_s_0(
  int32_t v5853[2][10],
  ac_channel< int32_t >& v5854,
  ac_channel< int32_t >& v5855,
  ac_channel< ac_int<26, false> >& v5856,
  ac_channel< ac_int<26, false> >& v5857
) {	// L9244
  int32_t k15[2];	// L9254
  for (int v5859 = 0; v5859 < 2; v5859++) {	// L9255
    k15[v5859] = 0;	// L9255
  }
  int32_t cret7[2];	// L9256
  for (int v5861 = 0; v5861 < 2; v5861++) {	// L9257
    cret7[v5861] = 0;	// L9257
  }
  int32_t zc7;	// L9258
  zc7 = 0;	// L9259
  int32_t v5863 = zc7;	// L9260
  v5854.write(v5863);	// L9261
  int32_t v5864 = zc7;	// L9262
  v5855.write(v5864);	// L9263
  int32_t v5865 = zc7;	// L9264
  v5854.write(v5865);	// L9265
  int32_t v5866 = zc7;	// L9266
  v5855.write(v5866);	// L9267
  int32_t v5867 = zc7;	// L9268
  v5854.write(v5867);	// L9269
  int32_t v5868 = zc7;	// L9270
  v5855.write(v5868);	// L9271
  int32_t v5869 = zc7;	// L9272
  v5854.write(v5869);	// L9273
  int32_t v5870 = zc7;	// L9274
  v5855.write(v5870);	// L9275
  int32_t v5871 = zc7;	// L9276
  v5854.write(v5871);	// L9277
  int32_t v5872 = zc7;	// L9278
  v5855.write(v5872);	// L9279
  cret7[0] = 2;	// L9280
  int32_t v5873 = cret7[0];	// L9281
  v5854.write(v5873);	// L9282
  cret7[1] = 2;	// L9283
  int32_t v5874 = cret7[1];	// L9284
  v5855.write(v5874);	// L9285
  l_S_t_0_t19: for (int t19 = 0; t19 < 10; t19++) {	// L9286
    ac_int<26, false> v5876 = v5856.read();	// L9287
    ac_int<26, false> pw14;	// L9288
    pw14 = v5876;	// L9289
    cret7[0] = 0;	// L9290
    ac_int<26, true> v5878 = pw14;	// L9291
    bool v5879;
    ap_int<26> v5879_tmp = v5878;
    v5879 = v5879_tmp[25];	// L9292
    int32_t v5880 = v5879;	// L9293
    bool v5881 = v5880 == 1;	// L9294
    if (v5881) {	// L9295
      cret7[0] = 1;	// L9296
      int32_t v5882 = k15[0];	// L9297
      bool v5883 = v5882 < 10;	// L9298
      if (v5883) {	// L9299
        ac_int<26, true> v5884 = pw14;	// L9300
        int32_t v5885 = v5884;	// L9301
        int32_t v5886 = v5885 & 67108863;	// L9302
        int32_t v5887 = k15[0];	// L9303
        int v5888 = v5887;	// L9304
        v5853[0][v5888] = v5886;	// L9305
        int32_t v5889 = k15[0];	// L9306
        ac_int<33, true> v5890 = v5889;	// L9307
        ac_int<33, true> v5891 = v5890 + 1;	// L9308
        int32_t v5892 = v5891;	// L9309
        k15[0] = v5892;	// L9310
      }
    }
    int32_t v5893 = cret7[0];	// L9313
    v5854.write(v5893);	// L9314
    ac_int<26, false> v5894 = v5857.read();	// L9315
    ac_int<26, false> pw15;	// L9316
    pw15 = v5894;	// L9317
    cret7[1] = 0;	// L9318
    ac_int<26, true> v5896 = pw15;	// L9319
    bool v5897;
    ap_int<26> v5897_tmp = v5896;
    v5897 = v5897_tmp[25];	// L9320
    int32_t v5898 = v5897;	// L9321
    bool v5899 = v5898 == 1;	// L9322
    if (v5899) {	// L9323
      cret7[1] = 1;	// L9324
      int32_t v5900 = k15[1];	// L9325
      bool v5901 = v5900 < 10;	// L9326
      if (v5901) {	// L9327
        ac_int<26, true> v5902 = pw15;	// L9328
        int32_t v5903 = v5902;	// L9329
        int32_t v5904 = v5903 & 67108863;	// L9330
        int32_t v5905 = k15[1];	// L9331
        int v5906 = v5905;	// L9332
        v5853[1][v5906] = v5904;	// L9333
        int32_t v5907 = k15[1];	// L9334
        ac_int<33, true> v5908 = v5907;	// L9335
        ac_int<33, true> v5909 = v5908 + 1;	// L9336
        int32_t v5910 = v5909;	// L9337
        k15[1] = v5910;	// L9338
      }
    }
    int32_t v5911 = cret7[1];	// L9341
    v5855.write(v5911);	// L9342
  }
}

/// This is top function.
void top(
  half v5912[2][10],
  int32_t v5913[2][10],
  half v5914[2][10],
  int32_t v5915[2][10],
  half v5916[2][10],
  int32_t v5917[2][10],
  half v5918[2][10],
  int32_t v5919[2][10],
  half v5920[2][10],
  half v5921[2][10],
  half v5922[2][10],
  half v5923[2][10],
  int32_t v5924[2][10],
  int32_t v5925[2][10],
  int32_t v5926[2][10],
  int32_t v5927[2][10],
  int32_t v5928[2][10],
  int32_t v5929[2][10],
  int32_t v5930[2][10],
  int32_t v5931[2][10]
) {	// L9346
  #pragma hls_design top

  #pragma hls_design dataflow
  ac_channel< ac_int<17, false> > v5932;
	// L9347
  ac_channel< ac_int<17, false> > v5933;
	// L9348
  ac_channel< ac_int<17, false> > v5934;
	// L9349
  ac_channel< ac_int<17, false> > v5935;
	// L9350
  ac_channel< ac_int<17, false> > v5936;
	// L9351
  ac_channel< ac_int<17, false> > v5937;
	// L9352
  ac_channel< ac_int<17, false> > v5938;
	// L9353
  ac_channel< ac_int<17, false> > v5939;
	// L9354
  ac_channel< ac_int<17, false> > v5940;
	// L9355
  ac_channel< ac_int<17, false> > v5941;
	// L9356
  ac_channel< ac_int<17, false> > v5942;
	// L9357
  ac_channel< ac_int<17, false> > v5943;
	// L9358
  ac_channel< ac_int<17, false> > v5944;
	// L9359
  ac_channel< ac_int<17, false> > v5945;
	// L9360
  ac_channel< ac_int<17, false> > v5946;
	// L9361
  ac_channel< ac_int<17, false> > v5947;
	// L9362
  ac_channel< ac_int<17, false> > v5948;
	// L9363
  ac_channel< ac_int<17, false> > v5949;
	// L9364
  ac_channel< ac_int<17, false> > v5950;
	// L9365
  ac_channel< ac_int<17, false> > v5951;
	// L9366
  ac_channel< ac_int<17, false> > v5952;
	// L9367
  ac_channel< ac_int<17, false> > v5953;
	// L9368
  ac_channel< ac_int<17, false> > v5954;
	// L9369
  ac_channel< ac_int<17, false> > v5955;
	// L9370
  ac_channel< ac_int<26, false> > v5956;
	// L9371
  ac_channel< ac_int<26, false> > v5957;
	// L9372
  ac_channel< ac_int<26, false> > v5958;
	// L9373
  ac_channel< ac_int<26, false> > v5959;
	// L9374
  ac_channel< ac_int<26, false> > v5960;
	// L9375
  ac_channel< ac_int<26, false> > v5961;
	// L9376
  ac_channel< ac_int<26, false> > v5962;
	// L9377
  ac_channel< ac_int<26, false> > v5963;
	// L9378
  ac_channel< ac_int<26, false> > v5964;
	// L9379
  ac_channel< ac_int<26, false> > v5965;
	// L9380
  ac_channel< ac_int<26, false> > v5966;
	// L9381
  ac_channel< ac_int<26, false> > v5967;
	// L9382
  ac_channel< ac_int<26, false> > v5968;
	// L9383
  ac_channel< ac_int<26, false> > v5969;
	// L9384
  ac_channel< ac_int<26, false> > v5970;
	// L9385
  ac_channel< ac_int<26, false> > v5971;
	// L9386
  ac_channel< ac_int<26, false> > v5972;
	// L9387
  ac_channel< ac_int<26, false> > v5973;
	// L9388
  ac_channel< ac_int<26, false> > v5974;
	// L9389
  ac_channel< ac_int<26, false> > v5975;
	// L9390
  ac_channel< ac_int<26, false> > v5976;
	// L9391
  ac_channel< ac_int<26, false> > v5977;
	// L9392
  ac_channel< ac_int<26, false> > v5978;
	// L9393
  ac_channel< ac_int<26, false> > v5979;
	// L9394
  ac_channel< int32_t > v5980;
	// L9395
  ac_channel< int32_t > v5981;
	// L9396
  ac_channel< int32_t > v5982;
	// L9397
  ac_channel< int32_t > v5983;
	// L9398
  ac_channel< int32_t > v5984;
	// L9399
  ac_channel< int32_t > v5985;
	// L9400
  ac_channel< int32_t > v5986;
	// L9401
  ac_channel< int32_t > v5987;
	// L9402
  ac_channel< int32_t > v5988;
	// L9403
  ac_channel< int32_t > v5989;
	// L9404
  ac_channel< int32_t > v5990;
	// L9405
  ac_channel< int32_t > v5991;
	// L9406
  ac_channel< int32_t > v5992;
	// L9407
  ac_channel< int32_t > v5993;
	// L9408
  ac_channel< int32_t > v5994;
	// L9409
  ac_channel< int32_t > v5995;
	// L9410
  ac_channel< int32_t > v5996;
	// L9411
  ac_channel< int32_t > v5997;
	// L9412
  ac_channel< int32_t > v5998;
	// L9413
  ac_channel< int32_t > v5999;
	// L9414
  ac_channel< int32_t > v6000;
	// L9415
  ac_channel< int32_t > v6001;
	// L9416
  ac_channel< int32_t > v6002;
	// L9417
  ac_channel< int32_t > v6003;
	// L9418
  ac_channel< int32_t > v6004;
	// L9419
  ac_channel< int32_t > v6005;
	// L9420
  ac_channel< int32_t > v6006;
	// L9421
  ac_channel< int32_t > v6007;
	// L9422
  ac_channel< int32_t > v6008;
	// L9423
  ac_channel< int32_t > v6009;
	// L9424
  ac_channel< int32_t > v6010;
	// L9425
  ac_channel< int32_t > v6011;
	// L9426
  ac_channel< int32_t > v6012;
	// L9427
  ac_channel< int32_t > v6013;
	// L9428
  ac_channel< int32_t > v6014;
	// L9429
  ac_channel< int32_t > v6015;
	// L9430
  ac_channel< int32_t > v6016;
	// L9431
  ac_channel< int32_t > v6017;
	// L9432
  ac_channel< int32_t > v6018;
	// L9433
  ac_channel< int32_t > v6019;
	// L9434
  ac_channel< int32_t > v6020;
	// L9435
  ac_channel< int32_t > v6021;
	// L9436
  ac_channel< int32_t > v6022;
	// L9437
  ac_channel< int32_t > v6023;
	// L9438
  ac_channel< int32_t > v6024;
	// L9439
  ac_channel< int32_t > v6025;
	// L9440
  ac_channel< int32_t > v6026;
	// L9441
  ac_channel< int32_t > v6027;
	// L9442
  node_0_0(v5957, v5962, v5970, v5974, v5933, v5938, v5946, v5950, v5980, v5987, v5992, v6000, v6004, v6011, v6016, v6024, v5956, v5963, v5968, v5976, v5981, v5986, v5994, v5998, v6022, v6018, v6010, v6005, v5932, v5939, v5944, v5952);	// L9443
  node_0_1(v5958, v5963, v5971, v5975, v5934, v5939, v5947, v5951, v5981, v5988, v5993, v6001, v6005, v6012, v6017, v6025, v5957, v5964, v5969, v5977, v5982, v5987, v5995, v5999, v6023, v6019, v6011, v6006, v5933, v5940, v5945, v5953);	// L9444
  node_1_0(v5960, v5965, v5972, v5976, v5936, v5941, v5948, v5952, v5983, v5990, v5994, v6002, v6007, v6014, v6018, v6026, v5959, v5966, v5970, v5978, v5984, v5989, v5996, v6000, v6024, v6020, v6013, v6008, v5935, v5942, v5946, v5954);	// L9445
  node_1_1(v5961, v5966, v5973, v5977, v5937, v5942, v5949, v5953, v5984, v5991, v5995, v6003, v6008, v6015, v6019, v6027, v5960, v5967, v5971, v5979, v5985, v5990, v5997, v6001, v6025, v6021, v6014, v6009, v5936, v5943, v5947, v5955);	// L9446
  drv_w_0(v5912, v5913, v5932, v5935, v6004, v6007);	// L9447
  drv_e_0(v5914, v5915, v5940, v5943, v6012, v6015);	// L9448
  drv_n_0(v5916, v5917, v5944, v5945, v6016, v6017);	// L9449
  drv_s_0(v5918, v5919, v5954, v5955, v6026, v6027);	// L9450
  col_w_0(v5920, v6010, v6013, v5938, v5941);	// L9451
  col_e_0(v5921, v6006, v6009, v5934, v5937);	// L9452
  col_n_0(v5922, v6022, v6023, v5950, v5951);	// L9453
  col_s_0(v5923, v6020, v6021, v5948, v5949);	// L9454
  rdrv_w_0(v5924, v5956, v5959, v5980, v5983);	// L9455
  rdrv_e_0(v5925, v5964, v5967, v5988, v5991);	// L9456
  rdrv_n_0(v5926, v5968, v5969, v5992, v5993);	// L9457
  rdrv_s_0(v5927, v5978, v5979, v6002, v6003);	// L9458
  rclc_w_0(v5928, v5986, v5989, v5962, v5965);	// L9459
  rclc_e_0(v5929, v5982, v5985, v5958, v5961);	// L9460
  rclc_n_0(v5930, v5998, v5999, v5974, v5975);	// L9461
  rclc_s_0(v5931, v5996, v5997, v5972, v5973);	// L9462
}

