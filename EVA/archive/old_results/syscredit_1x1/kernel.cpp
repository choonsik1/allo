
//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//
#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <hls_vector.h>
#include <math.h>
#include <stdint.h>
using namespace std;
void node_0_0(
  hls::stream< ap_uint<26> >& v0,
  hls::stream< ap_uint<26> >& v1,
  hls::stream< ap_uint<26> >& v2,
  hls::stream< ap_uint<26> >& v3,
  hls::stream< ap_uint<17> >& v4,
  hls::stream< ap_uint<17> >& v5,
  hls::stream< ap_uint<17> >& v6,
  hls::stream< ap_uint<17> >& v7,
  hls::stream< int32_t >& v8,
  hls::stream< int32_t >& v9,
  hls::stream< int32_t >& v10,
  hls::stream< int32_t >& v11,
  hls::stream< int32_t >& v12,
  hls::stream< int32_t >& v13,
  hls::stream< int32_t >& v14,
  hls::stream< int32_t >& v15,
  hls::stream< ap_uint<26> >& v16,
  hls::stream< ap_uint<26> >& v17,
  hls::stream< ap_uint<26> >& v18,
  hls::stream< ap_uint<26> >& v19,
  hls::stream< int32_t >& v20,
  hls::stream< int32_t >& v21,
  hls::stream< int32_t >& v22,
  hls::stream< int32_t >& v23,
  hls::stream< int32_t >& v24,
  hls::stream< int32_t >& v25,
  hls::stream< int32_t >& v26,
  hls::stream< int32_t >& v27,
  hls::stream< ap_uint<17> >& v28,
  hls::stream< ap_uint<17> >& v29,
  hls::stream< ap_uint<17> >& v30,
  hls::stream< ap_uint<17> >& v31
) {	// L4
  int32_t irf[8];	// L41
  #pragma HLS array_partition variable=irf complete dim=1

  for (int v33 = 0; v33 < 8; v33++) {	// L42
    irf[v33] = 0;	// L42
  }
  half drf[8];	// L43
  #pragma HLS array_partition variable=drf complete dim=1

  for (int v35 = 0; v35 < 8; v35++) {	// L44
    drf[v35] = (double)0.000000;	// L44
  }
  int32_t drf_full[8];	// L45
  #pragma HLS array_partition variable=drf_full complete dim=1

  for (int v37 = 0; v37 < 8; v37++) {	// L46
    drf_full[v37] = 0;	// L46
  }
  int32_t dsmask;	// L47
  dsmask = 0;	// L48
  int32_t crv_vld;	// L49
  crv_vld = 0;	// L50
  half crv_data;	// L51
  crv_data = (double)0.000000;	// L52
  int32_t crv_addr;	// L53
  crv_addr = 0;	// L54
  int32_t crv_mode;	// L55
  crv_mode = 0;	// L56
  int32_t crv_raw;	// L57
  crv_raw = 0;	// L58
  int32_t csd_vld;	// L59
  csd_vld = 0;	// L60
  ap_uint<26> csd_pkt;	// L61
  csd_pkt = 0;	// L62
  int32_t csd_dir;	// L63
  csd_dir = 0;	// L64
  int32_t row_id;	// L65
  row_id = 0;	// L66
  int32_t col_id;	// L67
  col_id = 0;	// L68
  ap_uint<26> oe_r;	// L69
  oe_r = 0;	// L70
  ap_uint<26> ow_r;	// L71
  ow_r = 0;	// L72
  ap_uint<26> on_r;	// L73
  on_r = 0;	// L74
  ap_uint<26> os_r;	// L75
  os_r = 0;	// L76
  ap_uint<17> txn_r;	// L77
  txn_r = 0;	// L78
  ap_uint<17> txs_r;	// L79
  txs_r = 0;	// L80
  ap_uint<17> txw_r;	// L81
  txw_r = 0;	// L82
  ap_uint<17> txe_r;	// L83
  txe_r = 0;	// L84
  half hold_v[4][2];	// L85
  #pragma HLS array_partition variable=hold_v complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=2

  for (int v58 = 0; v58 < 4; v58++) {	// L86
    for (int v59 = 0; v59 < 2; v59++) {	// L86
      hold_v[v58][v59] = (double)0.000000;	// L86
    }
  }
  uint8_t hold_cnt[4];	// L87
  #pragma HLS array_partition variable=hold_cnt complete dim=1

  for (int v61 = 0; v61 < 4; v61++) {	// L88
    hold_cnt[v61] = 0;	// L88
  }
  ap_uint<26> rbuf[4][2];	// L89
  #pragma HLS array_partition variable=rbuf complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=2

  for (int v63 = 0; v63 < 4; v63++) {	// L90
    for (int v64 = 0; v64 < 2; v64++) {	// L90
      rbuf[v63][v64] = 0;	// L90
    }
  }
  uint8_t rbcnt[4];	// L91
  #pragma HLS array_partition variable=rbcnt complete dim=1

  for (int v66 = 0; v66 < 4; v66++) {	// L92
    rbcnt[v66] = 0;	// L92
  }
  uint8_t rcred[4];	// L93
  #pragma HLS array_partition variable=rcred complete dim=1

  for (int v68 = 0; v68 < 4; v68++) {	// L94
    rcred[v68] = 0;	// L94
  }
  uint8_t cre_r;	// L95
  cre_r = 2;	// L96
  uint8_t crw_r;	// L97
  crw_r = 2;	// L98
  uint8_t crs_r;	// L99
  crs_r = 2;	// L100
  uint8_t crn_r;	// L101
  crn_r = 2;	// L102
  int32_t scred[4];	// L103
  #pragma HLS array_partition variable=scred complete dim=1

  for (int v74 = 0; v74 < 4; v74++) {	// L104
    scred[v74] = 0;	// L104
  }
  int32_t txp_v[4];	// L105
  #pragma HLS array_partition variable=txp_v complete dim=1

  for (int v76 = 0; v76 < 4; v76++) {	// L106
    txp_v[v76] = 0;	// L106
  }
  half txp_d[4];	// L107
  #pragma HLS array_partition variable=txp_d complete dim=1

  for (int v78 = 0; v78 < 4; v78++) {	// L108
    txp_d[v78] = (double)0.000000;	// L108
  }
  int32_t txp_r[4];	// L109
  #pragma HLS array_partition variable=txp_r complete dim=1

  for (int v80 = 0; v80 < 4; v80++) {	// L110
    txp_r[v80] = 0;	// L110
  }
  int32_t sc_r[4];	// L111
  #pragma HLS array_partition variable=sc_r complete dim=1

  for (int v82 = 0; v82 < 4; v82++) {	// L112
    sc_r[v82] = 2;	// L112
  }
  int32_t cfg_isz;	// L113
  cfg_isz = 0;	// L114
  int32_t cfg_itsz;	// L115
  cfg_itsz = 0;	// L116
  uint8_t fetch_en;	// L117
  fetch_en = 0;	// L118
  uint8_t instr_cnt;	// L119
  instr_cnt = 0;	// L120
  uint8_t iter_cnt;	// L121
  iter_cnt = 0;	// L122
  uint8_t condition_reg;	// L123
  condition_reg = 0;	// L124
  uint8_t sb_v[5];	// L125
  #pragma HLS array_partition variable=sb_v complete dim=1

  for (int v90 = 0; v90 < 5; v90++) {	// L126
    sb_v[v90] = 0;	// L126
  }
  uint8_t sb_dst[5];	// L127
  #pragma HLS array_partition variable=sb_dst complete dim=1

  for (int v92 = 0; v92 < 5; v92++) {	// L128
    sb_dst[v92] = 0;	// L128
  }
  uint8_t sb_cmp[5];	// L129
  #pragma HLS array_partition variable=sb_cmp complete dim=1

  for (int v94 = 0; v94 < 5; v94++) {	// L130
    sb_cmp[v94] = 0;	// L130
  }
  uint8_t sb_rtr[5];	// L131
  #pragma HLS array_partition variable=sb_rtr complete dim=1

  for (int v96 = 0; v96 < 5; v96++) {	// L132
    sb_rtr[v96] = 0;	// L132
  }
  uint8_t sb_inj[5];	// L133
  #pragma HLS array_partition variable=sb_inj complete dim=1

  for (int v98 = 0; v98 < 5; v98++) {	// L134
    sb_inj[v98] = 0;	// L134
  }
  uint8_t sb_dir[5];	// L135
  #pragma HLS array_partition variable=sb_dir complete dim=1

  for (int v100 = 0; v100 < 5; v100++) {	// L136
    sb_dir[v100] = 0;	// L136
  }
  uint8_t sb_id[5];	// L137
  #pragma HLS array_partition variable=sb_id complete dim=1

  for (int v102 = 0; v102 < 5; v102++) {	// L138
    sb_id[v102] = 0;	// L138
  }
  uint8_t sb_rvld[5];	// L139
  #pragma HLS array_partition variable=sb_rvld complete dim=1

  for (int v104 = 0; v104 < 5; v104++) {	// L140
    sb_rvld[v104] = 0;	// L140
  }
  uint8_t sb_ix[5];	// L141
  #pragma HLS array_partition variable=sb_ix complete dim=1

  for (int v106 = 0; v106 < 5; v106++) {	// L142
    sb_ix[v106] = 0;	// L142
  }
  uint8_t sb_long[5];	// L143
  #pragma HLS array_partition variable=sb_long complete dim=1

  for (int v108 = 0; v108 < 5; v108++) {	// L144
    sb_long[v108] = 0;	// L144
  }
  half resq[8];	// L145
  #pragma HLS array_partition variable=resq complete dim=1
#pragma HLS dependence variable=resq type=inter dependent=false

  for (int v110 = 0; v110 < 8; v110++) {	// L146
    resq[v110] = (double)0.000000;	// L146
  }
  uint8_t cmpq[8];	// L147
  #pragma HLS array_partition variable=cmpq complete dim=1
#pragma HLS dependence variable=cmpq type=inter dependent=false

  for (int v112 = 0; v112 < 8; v112++) {	// L148
    cmpq[v112] = 0;	// L148
  }
  uint8_t resq_wr;	// L149
  resq_wr = 0;	// L150
  ap_uint<26> zpkt;	// L151
  zpkt = 0;	// L152
  ap_uint<17> zsys;	// L153
  zsys = 0;	// L154
  int32_t zcr;	// L155
  zcr = 0;	// L156
  ap_int<26> v117 = zpkt;	// L157
  v0.write(v117);	// L158
  ap_int<26> v118 = zpkt;	// L159
  v1.write(v118);	// L160
  ap_int<26> v119 = zpkt;	// L161
  v2.write(v119);	// L162
  ap_int<26> v120 = zpkt;	// L163
  v3.write(v120);	// L164
  ap_int<17> v121 = zsys;	// L165
  v4.write(v121);	// L166
  ap_int<17> v122 = zsys;	// L167
  v5.write(v122);	// L168
  ap_int<17> v123 = zsys;	// L169
  v6.write(v123);	// L170
  ap_int<17> v124 = zsys;	// L171
  v7.write(v124);	// L172
  int32_t v125 = zcr;	// L173
  v8.write(v125);	// L174
  int32_t v126 = zcr;	// L175
  v9.write(v126);	// L176
  int32_t v127 = zcr;	// L177
  v10.write(v127);	// L178
  int32_t v128 = zcr;	// L179
  v11.write(v128);	// L180
  int32_t v129 = zcr;	// L181
  v12.write(v129);	// L182
  int32_t v130 = zcr;	// L183
  v13.write(v130);	// L184
  int32_t v131 = zcr;	// L185
  v14.write(v131);	// L186
  int32_t v132 = zcr;	// L187
  v15.write(v132);	// L188
  ap_int<26> v133 = zpkt;	// L189
  v0.write(v133);	// L190
  ap_int<26> v134 = zpkt;	// L191
  v1.write(v134);	// L192
  ap_int<26> v135 = zpkt;	// L193
  v2.write(v135);	// L194
  ap_int<26> v136 = zpkt;	// L195
  v3.write(v136);	// L196
  ap_int<17> v137 = zsys;	// L197
  v4.write(v137);	// L198
  ap_int<17> v138 = zsys;	// L199
  v5.write(v138);	// L200
  ap_int<17> v139 = zsys;	// L201
  v6.write(v139);	// L202
  ap_int<17> v140 = zsys;	// L203
  v7.write(v140);	// L204
  int32_t v141 = zcr;	// L205
  v8.write(v141);	// L206
  int32_t v142 = zcr;	// L207
  v9.write(v142);	// L208
  int32_t v143 = zcr;	// L209
  v10.write(v143);	// L210
  int32_t v144 = zcr;	// L211
  v11.write(v144);	// L212
  int32_t v145 = zcr;	// L213
  v12.write(v145);	// L214
  int32_t v146 = zcr;	// L215
  v13.write(v146);	// L216
  int32_t v147 = zcr;	// L217
  v14.write(v147);	// L218
  int32_t v148 = zcr;	// L219
  v15.write(v148);	// L220
  ap_int<26> v149 = zpkt;	// L221
  v0.write(v149);	// L222
  ap_int<26> v150 = zpkt;	// L223
  v1.write(v150);	// L224
  ap_int<26> v151 = zpkt;	// L225
  v2.write(v151);	// L226
  ap_int<26> v152 = zpkt;	// L227
  v3.write(v152);	// L228
  ap_int<17> v153 = zsys;	// L229
  v4.write(v153);	// L230
  ap_int<17> v154 = zsys;	// L231
  v5.write(v154);	// L232
  ap_int<17> v155 = zsys;	// L233
  v6.write(v155);	// L234
  ap_int<17> v156 = zsys;	// L235
  v7.write(v156);	// L236
  int32_t v157 = zcr;	// L237
  v8.write(v157);	// L238
  int32_t v158 = zcr;	// L239
  v9.write(v158);	// L240
  int32_t v159 = zcr;	// L241
  v10.write(v159);	// L242
  int32_t v160 = zcr;	// L243
  v11.write(v160);	// L244
  int32_t v161 = zcr;	// L245
  v12.write(v161);	// L246
  int32_t v162 = zcr;	// L247
  v13.write(v162);	// L248
  int32_t v163 = zcr;	// L249
  v14.write(v163);	// L250
  int32_t v164 = zcr;	// L251
  v15.write(v164);	// L252
  ap_int<26> v165 = zpkt;	// L253
  v0.write(v165);	// L254
  ap_int<26> v166 = zpkt;	// L255
  v1.write(v166);	// L256
  ap_int<26> v167 = zpkt;	// L257
  v2.write(v167);	// L258
  ap_int<26> v168 = zpkt;	// L259
  v3.write(v168);	// L260
  ap_int<17> v169 = zsys;	// L261
  v4.write(v169);	// L262
  ap_int<17> v170 = zsys;	// L263
  v5.write(v170);	// L264
  ap_int<17> v171 = zsys;	// L265
  v6.write(v171);	// L266
  ap_int<17> v172 = zsys;	// L267
  v7.write(v172);	// L268
  int32_t v173 = zcr;	// L269
  v8.write(v173);	// L270
  int32_t v174 = zcr;	// L271
  v9.write(v174);	// L272
  int32_t v175 = zcr;	// L273
  v10.write(v175);	// L274
  int32_t v176 = zcr;	// L275
  v11.write(v176);	// L276
  int32_t v177 = zcr;	// L277
  v12.write(v177);	// L278
  int32_t v178 = zcr;	// L279
  v13.write(v178);	// L280
  int32_t v179 = zcr;	// L281
  v14.write(v179);	// L282
  int32_t v180 = zcr;	// L283
  v15.write(v180);	// L284
  ap_int<26> v181 = zpkt;	// L285
  v0.write(v181);	// L286
  ap_int<26> v182 = zpkt;	// L287
  v1.write(v182);	// L288
  ap_int<26> v183 = zpkt;	// L289
  v2.write(v183);	// L290
  ap_int<26> v184 = zpkt;	// L291
  v3.write(v184);	// L292
  ap_int<17> v185 = zsys;	// L293
  v4.write(v185);	// L294
  ap_int<17> v186 = zsys;	// L295
  v5.write(v186);	// L296
  ap_int<17> v187 = zsys;	// L297
  v6.write(v187);	// L298
  ap_int<17> v188 = zsys;	// L299
  v7.write(v188);	// L300
  int32_t v189 = zcr;	// L301
  v8.write(v189);	// L302
  int32_t v190 = zcr;	// L303
  v9.write(v190);	// L304
  int32_t v191 = zcr;	// L305
  v10.write(v191);	// L306
  int32_t v192 = zcr;	// L307
  v11.write(v192);	// L308
  int32_t v193 = zcr;	// L309
  v12.write(v193);	// L310
  int32_t v194 = zcr;	// L311
  v13.write(v194);	// L312
  int32_t v195 = zcr;	// L313
  v14.write(v195);	// L314
  int32_t v196 = zcr;	// L315
  v15.write(v196);	// L316
  ap_int<26> v197 = oe_r;	// L317
  v0.write(v197);	// L318
  ap_int<26> v198 = ow_r;	// L319
  v1.write(v198);	// L320
  ap_int<26> v199 = os_r;	// L321
  v2.write(v199);	// L322
  ap_int<26> v200 = on_r;	// L323
  v3.write(v200);	// L324
  ap_int<17> v201 = txe_r;	// L325
  v4.write(v201);	// L326
  ap_int<17> v202 = txw_r;	// L327
  v5.write(v202);	// L328
  ap_int<17> v203 = txs_r;	// L329
  v6.write(v203);	// L330
  ap_int<17> v204 = txn_r;	// L331
  v7.write(v204);	// L332
  int8_t v205 = cre_r;	// L333
  v8.write(v205);	// L334
  int8_t v206 = crw_r;	// L335
  v9.write(v206);	// L336
  int8_t v207 = crs_r;	// L337
  v10.write(v207);	// L338
  int8_t v208 = crn_r;	// L339
  v11.write(v208);	// L340
  int32_t v209 = sc_r[0];	// L341
  v14.write(v209);	// L342
  int32_t v210 = sc_r[1];	// L343
  v15.write(v210);	// L344
  int32_t v211 = sc_r[2];	// L345
  v12.write(v211);	// L346
  int32_t v212 = sc_r[3];	// L347
  v13.write(v212);	// L348
  l_S_t_0_t: for (int t = 0; t < 200; t++) {	// L349
  #pragma HLS pipeline II=1
    ap_uint<26> v214 = v16.read();	// L350
    ap_uint<26> p_w;	// L351
    p_w = v214;	// L352
    ap_uint<26> v216 = v17.read();	// L353
    ap_uint<26> p_e;	// L354
    p_e = v216;	// L355
    ap_uint<26> v218 = v18.read();	// L356
    ap_uint<26> p_n;	// L357
    p_n = v218;	// L358
    ap_uint<26> v220 = v19.read();	// L359
    ap_uint<26> p_s;	// L360
    p_s = v220;	// L361
    int32_t v222 = v20.read();	// L362
    uint8_t v223 = rcred[0];	// L363
    ap_int<33> v224 = v223;	// L364
    ap_int<33> v225 = v222;	// L365
    ap_int<33> v226 = v224 + v225;	// L366
    uint8_t v227 = v226;	// L367
    rcred[0] = v227;	// L368
    int32_t v228 = v21.read();	// L369
    uint8_t v229 = rcred[1];	// L370
    ap_int<33> v230 = v229;	// L371
    ap_int<33> v231 = v228;	// L372
    ap_int<33> v232 = v230 + v231;	// L373
    uint8_t v233 = v232;	// L374
    rcred[1] = v233;	// L375
    int32_t v234 = v22.read();	// L376
    uint8_t v235 = rcred[2];	// L377
    ap_int<33> v236 = v235;	// L378
    ap_int<33> v237 = v234;	// L379
    ap_int<33> v238 = v236 + v237;	// L380
    uint8_t v239 = v238;	// L381
    rcred[2] = v239;	// L382
    int32_t v240 = v23.read();	// L383
    uint8_t v241 = rcred[3];	// L384
    ap_int<33> v242 = v241;	// L385
    ap_int<33> v243 = v240;	// L386
    ap_int<33> v244 = v242 + v243;	// L387
    uint8_t v245 = v244;	// L388
    rcred[3] = v245;	// L389
    int32_t v246 = v24.read();	// L390
    int32_t v247 = scred[0];	// L391
    ap_int<33> v248 = v247;	// L392
    ap_int<33> v249 = v246;	// L393
    ap_int<33> v250 = v248 + v249;	// L394
    int32_t v251 = v250;	// L395
    scred[0] = v251;	// L396
    int32_t v252 = v25.read();	// L397
    int32_t v253 = scred[1];	// L398
    ap_int<33> v254 = v253;	// L399
    ap_int<33> v255 = v252;	// L400
    ap_int<33> v256 = v254 + v255;	// L401
    int32_t v257 = v256;	// L402
    scred[1] = v257;	// L403
    int32_t v258 = v26.read();	// L404
    int32_t v259 = scred[2];	// L405
    ap_int<33> v260 = v259;	// L406
    ap_int<33> v261 = v258;	// L407
    ap_int<33> v262 = v260 + v261;	// L408
    int32_t v263 = v262;	// L409
    scred[2] = v263;	// L410
    int32_t v264 = v27.read();	// L411
    int32_t v265 = scred[3];	// L412
    ap_int<33> v266 = v265;	// L413
    ap_int<33> v267 = v264;	// L414
    ap_int<33> v268 = v266 + v267;	// L415
    int32_t v269 = v268;	// L416
    scred[3] = v269;	// L417
    ap_uint<26> fin[4];	// L418
    for (int v271 = 0; v271 < 4; v271++) {	// L419
      fin[v271] = 0;	// L419
    }
    ap_int<26> v272 = p_w;	// L420
    fin[0] = v272;	// L421
    ap_int<26> v273 = p_e;	// L422
    fin[1] = v273;	// L423
    ap_int<26> v274 = p_n;	// L424
    fin[2] = v274;	// L425
    ap_int<26> v275 = p_s;	// L426
    fin[3] = v275;	// L427
    l_S_d_0_d: for (int d = 0; d < 4; d++) {	// L428
      ap_uint<26> v277 = fin[d];	// L429
      bool v278;
      ap_int<26> v278_tmp = v277;
      v278 = v278_tmp[25];	// L430
      int32_t v279 = v278;	// L431
      bool v280 = v279 == 1;	// L432
      uint8_t v281 = rbcnt[d];	// L433
      int32_t v282 = v281;	// L434
      bool v283 = v282 < 2;	// L435
      bool v284 = v280 & v283;	// L436
      if (v284) {	// L437
        ap_uint<26> v285 = fin[d];	// L438
        uint8_t v286 = rbcnt[d];	// L439
        int v287 = v286;	// L440
        rbuf[d][v287] = v285;	// L441
        uint8_t v288 = rbcnt[d];	// L442
        ap_int<33> v289 = v288;	// L443
        ap_int<33> v290 = v289 + 1;	// L444
        uint8_t v291 = v290;	// L445
        rbcnt[d] = v291;	// L446
      }
    }
    ap_uint<26> hd[4];	// L449
    for (int v293 = 0; v293 < 4; v293++) {	// L450
      hd[v293] = 0;	// L450
    }
    int32_t hvld[4];	// L451
    for (int v295 = 0; v295 < 4; v295++) {	// L452
      hvld[v295] = 0;	// L452
    }
    int32_t hit[4];	// L453
    for (int v297 = 0; v297 < 4; v297++) {	// L454
      hit[v297] = 0;	// L454
    }
    int32_t axis[4];	// L455
    for (int v299 = 0; v299 < 4; v299++) {	// L456
      axis[v299] = 0;	// L456
    }
    int32_t v300 = col_id;	// L457
    axis[0] = v300;	// L458
    int32_t v301 = col_id;	// L459
    axis[1] = v301;	// L460
    int32_t v302 = row_id;	// L461
    axis[2] = v302;	// L462
    int32_t v303 = row_id;	// L463
    axis[3] = v303;	// L464
    l_S_d_1_d1: for (int d1 = 0; d1 < 4; d1++) {	// L465
      uint8_t v305 = rbcnt[d1];	// L466
      int32_t v306 = v305;	// L467
      bool v307 = v306 > 0;	// L468
      if (v307) {	// L469
        ap_uint<26> v308 = rbuf[d1][0];	// L470
        hd[d1] = v308;	// L471
        hvld[d1] = 1;	// L472
        ap_uint<26> v309 = hd[d1];	// L473
        ap_int<4> v310;
        ap_int<26> v310_tmp = v309;
        v310 = v310_tmp(24, 21);	// L474
        int32_t v311 = axis[d1];	// L475
        int32_t v312 = v310;	// L476
        bool v313 = v312 == v311;	// L477
        if (v313) {	// L478
          hit[d1] = 1;	// L479
        }
      }
    }
    ap_uint<26> o_crv;	// L483
    o_crv = 0;	// L484
    int32_t crv_in;	// L485
    crv_in = -1;	// L486
    int32_t v316 = hit[3];	// L487
    bool v317 = v316 == 1;	// L488
    if (v317) {	// L489
      ap_uint<26> v318 = hd[3];	// L490
      o_crv = v318;	// L491
      crv_in = 3;	// L492
    } else {
      int32_t v319 = hit[2];	// L494
      bool v320 = v319 == 1;	// L495
      if (v320) {	// L496
        ap_uint<26> v321 = hd[2];	// L497
        o_crv = v321;	// L498
        crv_in = 2;	// L499
      } else {
        int32_t v322 = hit[1];	// L501
        bool v323 = v322 == 1;	// L502
        if (v323) {	// L503
          ap_uint<26> v324 = hd[1];	// L504
          o_crv = v324;	// L505
          crv_in = 1;	// L506
        } else {
          int32_t v325 = hit[0];	// L508
          bool v326 = v325 == 1;	// L509
          if (v326) {	// L510
            ap_uint<26> v327 = hd[0];	// L511
            o_crv = v327;	// L512
            crv_in = 0;	// L513
          }
        }
      }
    }
    ap_uint<26> o_out[4];	// L518
    for (int v329 = 0; v329 < 4; v329++) {	// L519
      o_out[v329] = 0;	// L519
    }
    int32_t pop[4];	// L520
    for (int v331 = 0; v331 < 4; v331++) {	// L521
      pop[v331] = 0;	// L521
    }
    int32_t inj_done;	// L522
    inj_done = 0;	// L523
    int32_t idir;	// L524
    idir = -1;	// L525
    ap_int<26> v334 = csd_pkt;	// L526
    bool v335;
    ap_int<26> v335_tmp = v334;
    v335 = v335_tmp[25];	// L527
    int32_t v336 = v335;	// L528
    bool v337 = v336 == 1;	// L529
    if (v337) {	// L530
      int32_t v338 = csd_dir;	// L531
      ap_int<33> v339 = v338;	// L532
      ap_int<33> v340 = 3 - v339;	// L533
      int32_t v341 = v340;	// L534
      idir = v341;	// L535
    }
    l_S_o_2_o: for (int o = 0; o < 4; o++) {	// L537
      uint8_t v343 = rcred[o];	// L538
      int32_t v344 = v343;	// L539
      bool v345 = v344 > 0;	// L540
      if (v345) {	// L541
        int32_t v346 = idir;	// L542
        ap_int<33> v347 = v346;	// L543
        ap_int<33> v348 = o;	// L544
        bool v349 = v347 == v348;	// L545
        if (v349) {	// L546
          ap_int<26> v350 = csd_pkt;	// L547
          o_out[o] = v350;	// L548
          uint8_t v351 = rcred[o];	// L549
          ap_int<33> v352 = v351;	// L550
          ap_int<33> v353 = v352 - 1;	// L551
          uint8_t v354 = v353;	// L552
          rcred[o] = v354;	// L553
          inj_done = 1;	// L554
        } else {
          int32_t v355 = hvld[o];	// L556
          bool v356 = v355 == 1;	// L557
          int32_t v357 = hit[o];	// L558
          bool v358 = v357 == 0;	// L559
          bool v359 = v356 & v358;	// L560
          if (v359) {	// L561
            ap_uint<26> v360 = hd[o];	// L562
            o_out[o] = v360;	// L563
            uint8_t v361 = rcred[o];	// L564
            ap_int<33> v362 = v361;	// L565
            ap_int<33> v363 = v362 - 1;	// L566
            uint8_t v364 = v363;	// L567
            rcred[o] = v364;	// L568
            pop[o] = 1;	// L569
          }
        }
      }
    }
    int32_t v365 = crv_in;	// L574
    bool v366 = v365 >= 0;	// L575
    if (v366) {	// L576
      int32_t v367 = crv_in;	// L577
      int v368 = v367;	// L578
      pop[v368] = 1;	// L579
    }
    int32_t ret[4];	// L581
    for (int v370 = 0; v370 < 4; v370++) {	// L582
      ret[v370] = 0;	// L582
    }
    l_S_d_3_d2: for (int d2 = 0; d2 < 4; d2++) {	// L583
      int32_t v372 = pop[d2];	// L584
      bool v373 = v372 == 1;	// L585
      if (v373) {	// L586
        l_S_sft_3_sft: for (int sft = 0; sft < 1; sft++) {	// L587
          ap_uint<26> v375 = rbuf[d2][(sft + 1)];	// L588
          rbuf[d2][sft] = v375;	// L589
        }
        uint8_t v376 = rbcnt[d2];	// L591
        ap_int<33> v377 = v376;	// L592
        ap_int<33> v378 = v377 - 1;	// L593
        uint8_t v379 = v378;	// L594
        rbcnt[d2] = v379;	// L595
        ret[d2] = 1;	// L596
      }
    }
    int32_t v380 = ret[0];	// L599
    uint8_t v381 = v380;	// L600
    cre_r = v381;	// L601
    int32_t v382 = ret[1];	// L602
    uint8_t v383 = v382;	// L603
    crw_r = v383;	// L604
    int32_t v384 = ret[2];	// L605
    uint8_t v385 = v384;	// L606
    crs_r = v385;	// L607
    int32_t v386 = ret[3];	// L608
    uint8_t v387 = v386;	// L609
    crn_r = v387;	// L610
    ap_uint<26> v388 = o_out[0];	// L611
    oe_r = v388;	// L612
    ap_uint<26> v389 = o_out[1];	// L613
    ow_r = v389;	// L614
    ap_uint<26> v390 = o_out[2];	// L615
    os_r = v390;	// L616
    ap_uint<26> v391 = o_out[3];	// L617
    on_r = v391;	// L618
    int32_t v392 = inj_done;	// L619
    bool v393 = v392 == 1;	// L620
    if (v393) {	// L621
      csd_pkt = 0;	// L622
    }
    ap_int<26> v394 = o_crv;	// L624
    bool v395;
    ap_int<26> v395_tmp = v394;
    v395 = v395_tmp[25];	// L625
    int32_t v396 = v395;	// L626
    crv_vld = v396;	// L627
    ap_int<26> v397 = o_crv;	// L628
    int16_t v398;
    ap_int<26> v398_tmp = v397;
    v398 = v398_tmp(15, 0);	// L629
    half v399;
    union { uint16_t from; half to;} _converter_v398_to_v399 = {};
    _converter_v398_to_v399.from = v398;
    v399 = _converter_v398_to_v399.to;	// L630
    crv_data = v399;	// L631
    ap_int<26> v400 = o_crv;	// L632
    ap_int<4> v401;
    ap_int<26> v401_tmp = v400;
    v401 = v401_tmp(19, 16);	// L633
    int32_t v402 = v401;	// L634
    crv_addr = v402;	// L635
    ap_int<26> v403 = o_crv;	// L636
    bool v404;
    ap_int<26> v404_tmp = v403;
    v404 = v404_tmp[20];	// L637
    int32_t v405 = v404;	// L638
    crv_mode = v405;	// L639
    ap_int<26> v406 = o_crv;	// L640
    int16_t v407;
    ap_int<26> v407_tmp = v406;
    v407 = v407_tmp(15, 0);	// L641
    int32_t v408 = v407;	// L642
    crv_raw = v408;	// L643
    ap_uint<17> v409 = v28.read();	// L644
    ap_uint<17> rx_w;	// L645
    rx_w = v409;	// L646
    ap_uint<17> v411 = v29.read();	// L647
    ap_uint<17> rx_e;	// L648
    rx_e = v411;	// L649
    ap_uint<17> v413 = v30.read();	// L650
    ap_uint<17> rx_n;	// L651
    rx_n = v413;	// L652
    ap_uint<17> v415 = v31.read();	// L653
    ap_uint<17> rx_s;	// L654
    rx_s = v415;	// L655
    half rxv[4];	// L656
    for (int v418 = 0; v418 < 4; v418++) {	// L657
      rxv[v418] = (double)0.000000;	// L657
    }
    int32_t rxvld[4];	// L658
    for (int v420 = 0; v420 < 4; v420++) {	// L659
      rxvld[v420] = 0;	// L659
    }
    ap_int<17> v421 = rx_n;	// L660
    int16_t v422;
    ap_int<17> v422_tmp = v421;
    v422 = v422_tmp(16, 1);	// L661
    half v423;
    union { uint16_t from; half to;} _converter_v422_to_v423 = {};
    _converter_v422_to_v423.from = v422;
    v423 = _converter_v422_to_v423.to;	// L662
    rxv[0] = v423;	// L663
    ap_int<17> v424 = rx_n;	// L664
    bool v425;
    ap_int<17> v425_tmp = v424;
    v425 = v425_tmp[0];	// L665
    int32_t v426 = v425;	// L666
    rxvld[0] = v426;	// L667
    ap_int<17> v427 = rx_s;	// L668
    int16_t v428;
    ap_int<17> v428_tmp = v427;
    v428 = v428_tmp(16, 1);	// L669
    half v429;
    union { uint16_t from; half to;} _converter_v428_to_v429 = {};
    _converter_v428_to_v429.from = v428;
    v429 = _converter_v428_to_v429.to;	// L670
    rxv[1] = v429;	// L671
    ap_int<17> v430 = rx_s;	// L672
    bool v431;
    ap_int<17> v431_tmp = v430;
    v431 = v431_tmp[0];	// L673
    int32_t v432 = v431;	// L674
    rxvld[1] = v432;	// L675
    ap_int<17> v433 = rx_w;	// L676
    int16_t v434;
    ap_int<17> v434_tmp = v433;
    v434 = v434_tmp(16, 1);	// L677
    half v435;
    union { uint16_t from; half to;} _converter_v434_to_v435 = {};
    _converter_v434_to_v435.from = v434;
    v435 = _converter_v434_to_v435.to;	// L678
    rxv[2] = v435;	// L679
    ap_int<17> v436 = rx_w;	// L680
    bool v437;
    ap_int<17> v437_tmp = v436;
    v437 = v437_tmp[0];	// L681
    int32_t v438 = v437;	// L682
    rxvld[2] = v438;	// L683
    ap_int<17> v439 = rx_e;	// L684
    int16_t v440;
    ap_int<17> v440_tmp = v439;
    v440 = v440_tmp(16, 1);	// L685
    half v441;
    union { uint16_t from; half to;} _converter_v440_to_v441 = {};
    _converter_v440_to_v441.from = v440;
    v441 = _converter_v440_to_v441.to;	// L686
    rxv[3] = v441;	// L687
    ap_int<17> v442 = rx_e;	// L688
    bool v443;
    ap_int<17> v443_tmp = v442;
    v443 = v443_tmp[0];	// L689
    int32_t v444 = v443;	// L690
    rxvld[3] = v444;	// L691
    l_S_d_5_d3: for (int d3 = 0; d3 < 4; d3++) {	// L692
      int32_t v446 = rxvld[d3];	// L693
      bool v447 = v446 == 1;	// L694
      uint8_t v448 = hold_cnt[d3];	// L695
      int32_t v449 = v448;	// L696
      bool v450 = v449 < 2;	// L697
      bool v451 = v447 & v450;	// L698
      if (v451) {	// L699
        half v452 = rxv[d3];	// L700
        uint8_t v453 = hold_cnt[d3];	// L701
        int v454 = v453;	// L702
        hold_v[d3][v454] = v452;	// L703
        uint8_t v455 = hold_cnt[d3];	// L704
        ap_int<33> v456 = v455;	// L705
        ap_int<33> v457 = v456 + 1;	// L706
        uint8_t v458 = v457;	// L707
        hold_cnt[d3] = v458;	// L708
      }
    }
    int32_t retire_ok;	// L711
    retire_ok = 1;	// L712
    uint8_t v460 = sb_v[0];	// L713
    int32_t v461 = v460;	// L714
    bool v462 = v461 == 1;	// L715
    uint8_t v463 = sb_rtr[0];	// L716
    int32_t v464 = v463;	// L717
    bool v465 = v464 == 0;	// L718
    uint8_t v466 = sb_dst[0];	// L719
    int32_t v467 = v466;	// L720
    bool v468 = v467 >= 12;	// L721
    bool v469 = v462 & v465;	// L722
    bool v470 = v469 & v468;	// L723
    if (v470) {	// L724
      uint8_t v471 = sb_rvld[0];	// L725
      int32_t v472 = v471;	// L726
      bool v473 = v472 == 1;	// L727
      uint8_t v474 = sb_dst[0];	// L728
      int32_t v475 = v474;	// L729
      int32_t v476 = v475 & 3;	// L730
      int v477 = v476;	// L731
      int32_t v478 = txp_v[v477];	// L732
      bool v479 = v478 == 1;	// L733
      bool v480 = v473 & v479;	// L734
      if (v480) {	// L735
        retire_ok = 0;	// L736
      }
    }
    uint8_t v481 = sb_v[0];	// L739
    int32_t v482 = v481;	// L740
    bool v483 = v482 == 1;	// L741
    int32_t v484 = retire_ok;	// L742
    bool v485 = v484 == 1;	// L743
    bool v486 = v483 & v485;	// L744
    if (v486) {	// L745
      uint8_t v487 = sb_ix[0];	// L746
      int v488 = v487;	// L747
      half v489 = resq[v488];	// L748
      half wb;
#pragma HLS dependence variable=wb type=inter dependent=false	// L749
      wb = v489;	// L750
      uint8_t v491 = sb_cmp[0];	// L751
      int32_t v492 = v491;	// L752
      bool v493 = v492 == 1;	// L753
      if (v493) {	// L754
        uint8_t v494 = sb_ix[0];	// L755
        int v495 = v494;	// L756
        uint8_t v496 = cmpq[v495];	// L757
        condition_reg = v496;	// L758
      }
      uint8_t v497 = sb_rtr[0];	// L760
      int32_t v498 = v497;	// L761
      bool v499 = v498 == 1;	// L762
      if (v499) {	// L763
        uint8_t v500 = sb_inj[0];	// L764
        int32_t v501 = v500;	// L765
        bool v502 = v501 == 1;	// L766
        ap_int<26> v503 = csd_pkt;	// L767
        bool v504;
        ap_int<26> v504_tmp = v503;
        v504 = v504_tmp[25];	// L768
        int32_t v505 = v504;	// L769
        bool v506 = v505 == 0;	// L770
        bool v507 = v502 & v506;	// L771
        if (v507) {	// L772
          half v508 = wb;	// L773
          uint16_t v509;
          union { half from; uint16_t to;} _converter_v508_to_v509 = {};
          _converter_v508_to_v509.from = v508;
          v509 = _converter_v508_to_v509.to;	// L774
          ap_int<26> v510 = csd_pkt;	// L775
          ap_int<26> v511;
          ap_int<26> v511_tmp = v510;
          v511_tmp(15, 0) = v509;
          v511 = v511_tmp;	// L776
          csd_pkt = v511;	// L777
          uint8_t v512 = sb_dst[0];	// L778
          ap_uint<4> v513 = v512;	// L779
          ap_int<26> v514 = csd_pkt;	// L780
          ap_int<26> v515;
          ap_int<26> v515_tmp = v514;
          v515_tmp(19, 16) = v513;
          v515 = v515_tmp;	// L781
          csd_pkt = v515;	// L782
          uint8_t v516 = sb_id[0];	// L783
          ap_uint<4> v517 = v516;	// L784
          ap_int<26> v518 = csd_pkt;	// L785
          ap_int<26> v519;
          ap_int<26> v519_tmp = v518;
          v519_tmp(24, 21) = v517;
          v519 = v519_tmp;	// L786
          csd_pkt = v519;	// L787
          uint8_t v520 = sb_rvld[0];	// L788
          bool v521 = v520;	// L789
          ap_int<26> v522 = csd_pkt;	// L790
          ap_int<26> v523;
          ap_int<26> v523_tmp = v522;
          v523_tmp[25] = v521;          v523 = v523_tmp;	// L791
          csd_pkt = v523;	// L792
          uint8_t v524 = sb_dir[0];	// L793
          int32_t v525 = v524;	// L794
          csd_dir = v525;	// L795
        }
      } else {
        uint8_t v526 = sb_dst[0];	// L798
        int32_t v527 = v526;	// L799
        bool v528 = v527 >= 12;	// L800
        if (v528) {	// L801
          uint8_t v529 = sb_rvld[0];	// L802
          int32_t v530 = v529;	// L803
          bool v531 = v530 == 1;	// L804
          if (v531) {	// L805
            uint8_t v532 = sb_dst[0];	// L806
            int32_t v533 = v532;	// L807
            int32_t v534 = v533 & 3;	// L808
            int v535 = v534;	// L809
            txp_v[v535] = 1;	// L810
            half v536 = wb;	// L811
            uint8_t v537 = sb_dst[0];	// L812
            int32_t v538 = v537;	// L813
            int32_t v539 = v538 & 3;	// L814
            int v540 = v539;	// L815
            txp_d[v540] = v536;	// L816
            uint8_t v541 = sb_dst[0];	// L817
            int32_t v542 = v541;	// L818
            int32_t v543 = v542 & 3;	// L819
            int v544 = v543;	// L820
            txp_r[v544] = 1;	// L821
          }
        } else {
          uint8_t v545 = sb_rvld[0];	// L824
          int32_t v546 = v545;	// L825
          bool v547 = v546 == 1;	// L826
          if (v547) {	// L827
            uint8_t v548 = sb_dst[0];	// L828
            int32_t v549 = v548;	// L829
            bool v550 = v549 < 8;	// L830
            int32_t v551 = dsmask;	// L831
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
    int32_t v638 = v637 >> v635;	// L968
    int32_t v639 = v638 & 1;	// L969
    bool v640 = v639 == 1;	// L970
    bool v641 = v636 & v640;	// L971
    if (v641) {	// L972
      int32_t v642 = s1;	// L973
      int v643 = v642;	// L974
      int32_t v644 = drf_full[v643];	// L975
      bool v645 = v644 == 0;	// L976
      if (v645) {	// L977
        a_vld = 0;	// L978
      }
    }
    int32_t v646 = s2;	// L981
    bool v647 = v646 < 8;	// L982
    int32_t v648 = dsmask;	// L983
    int32_t v649 = v648 >> v646;	// L984
    int32_t v650 = v649 & 1;	// L985
    bool v651 = v650 == 1;	// L986
    bool v652 = v647 & v651;	// L987
    if (v652) {	// L988
      int32_t v653 = s2;	// L989
      int v654 = v653;	// L990
      int32_t v655 = drf_full[v654];	// L991
      bool v656 = v655 == 0;	// L992
      if (v656) {	// L993
        b_vld = 0;	// L994
      }
    }
    int32_t binop;	// L997
    binop = 0;	// L998
    int32_t v658 = op;	// L999
    bool v659 = v658 == 0;	// L1000
    bool v660 = v658 == 1;	// L1001
    bool v661 = v658 == 2;	// L1002
    bool v662 = v658 == 8;	// L1003
    bool v663 = v658 == 9;	// L1004
    bool v664 = v659 | v660;	// L1005
    bool v665 = v664 | v661;	// L1006
    bool v666 = v665 | v662;	// L1007
    bool v667 = v666 | v663;	// L1008
    if (v667) {	// L1009
      binop = 1;	// L1010
    }
    int32_t raw;	// L1012
    raw = 0;	// L1013
    int32_t cmp_busy;	// L1014
    cmp_busy = 0;	// L1015
    int32_t fwd_a;	// L1016
    fwd_a = 0;	// L1017
    int32_t fwd_a_ix;	// L1018
    fwd_a_ix = 0;	// L1019
    int32_t raw_a;	// L1020
    raw_a = 0;	// L1021
    int32_t fwd_b;	// L1022
    fwd_b = 0;	// L1023
    int32_t fwd_b_ix;	// L1024
    fwd_b_ix = 0;	// L1025
    int32_t raw_b;	// L1026
    raw_b = 0;	// L1027
    l_S_k_6_k: for (int k = 0; k < 4; k++) {	// L1028
      ap_int<34> v677 = k;	// L1029
      ap_int<34> v678 = v677 + 1;	// L1030
      int32_t v679 = v678;	// L1031
      int32_t kk;	// L1032
      kk = v679;	// L1033
      int32_t v681 = kk;	// L1034
      ap_int<34> v682 = v681;	// L1035
      ap_int<34> v683 = 4 - v682;	// L1036
      int32_t v684 = v683;	// L1037
      int32_t inflight;	// L1038
      inflight = v684;	// L1039
      int32_t need;	// L1040
      need = 0;	// L1041
      int32_t v687 = kk;	// L1042
      int v688 = v687;	// L1043
      uint8_t v689 = sb_long[v688];	// L1044
      int32_t v690 = v689;	// L1045
      bool v691 = v690 == 1;	// L1046
      if (v691) {	// L1047
        need = 1;	// L1048
      }
      int32_t rdy;	// L1050
      rdy = 0;	// L1051
      int32_t v693 = inflight;	// L1052
      int32_t v694 = need;	// L1053
      bool v695 = v693 >= v694;	// L1054
      if (v695) {	// L1055
        rdy = 1;	// L1056
      }
      int32_t v696 = kk;	// L1058
      int v697 = v696;	// L1059
      uint8_t v698 = sb_v[v697];	// L1060
      int32_t v699 = v698;	// L1061
      bool v700 = v699 == 1;	// L1062
      uint8_t v701 = sb_rtr[v697];	// L1063
      int32_t v702 = v701;	// L1064
      bool v703 = v702 == 0;	// L1065
      uint8_t v704 = sb_dst[v697];	// L1066
      int32_t v705 = v704;	// L1067
      bool v706 = v705 < 12;	// L1068
      bool v707 = v700 & v703;	// L1069
      bool v708 = v707 & v706;	// L1070
      if (v708) {	// L1071
        int32_t v709 = s1;	// L1072
        bool v710 = v709 < 12;	// L1073
        int32_t v711 = kk;	// L1074
        int v712 = v711;	// L1075
        uint8_t v713 = sb_dst[v712];	// L1076
        int32_t v714 = v713;	// L1077
        int32_t v715 = v714 & 7;	// L1078
        int32_t v716 = v709 & 7;	// L1079
        bool v717 = v715 == v716;	// L1080
        bool v718 = v710 & v717;	// L1081
        if (v718) {	// L1082
          int32_t v719 = rdy;	// L1083
          bool v720 = v719 == 1;	// L1084
          if (v720) {	// L1085
            fwd_a = 1;	// L1086
            int32_t v721 = kk;	// L1087
            int v722 = v721;	// L1088
            uint8_t v723 = sb_ix[v722];	// L1089
            int32_t v724 = v723;	// L1090
            fwd_a_ix = v724;	// L1091
            raw_a = 0;	// L1092
          } else {
            fwd_a = 0;	// L1094
            raw_a = 1;	// L1095
          }
        }
        int32_t v725 = binop;	// L1098
        bool v726 = v725 == 1;	// L1099
        int32_t v727 = s2;	// L1100
        bool v728 = v727 < 12;	// L1101
        int32_t v729 = kk;	// L1102
        int v730 = v729;	// L1103
        uint8_t v731 = sb_dst[v730];	// L1104
        int32_t v732 = v731;	// L1105
        int32_t v733 = v732 & 7;	// L1106
        int32_t v734 = v727 & 7;	// L1107
        bool v735 = v733 == v734;	// L1108
        bool v736 = v726 & v728;	// L1109
        bool v737 = v736 & v735;	// L1110
        if (v737) {	// L1111
          int32_t v738 = rdy;	// L1112
          bool v739 = v738 == 1;	// L1113
          if (v739) {	// L1114
            fwd_b = 1;	// L1115
            int32_t v740 = kk;	// L1116
            int v741 = v740;	// L1117
            uint8_t v742 = sb_ix[v741];	// L1118
            int32_t v743 = v742;	// L1119
            fwd_b_ix = v743;	// L1120
            raw_b = 0;	// L1121
          } else {
            fwd_b = 0;	// L1123
            raw_b = 1;	// L1124
          }
        }
      }
      int32_t v744 = kk;	// L1128
      int v745 = v744;	// L1129
      uint8_t v746 = sb_v[v745];	// L1130
      int32_t v747 = v746;	// L1131
      bool v748 = v747 == 1;	// L1132
      uint8_t v749 = sb_cmp[v745];	// L1133
      int32_t v750 = v749;	// L1134
      bool v751 = v750 == 1;	// L1135
      bool v752 = v748 & v751;	// L1136
      if (v752) {	// L1137
        cmp_busy = 1;	// L1138
      }
    }
    int32_t v753 = raw_a;	// L1141
    raw = v753;	// L1142
    int32_t v754 = binop;	// L1143
    bool v755 = v754 == 1;	// L1144
    int32_t v756 = raw_b;	// L1145
    bool v757 = v756 == 1;	// L1146
    bool v758 = v755 & v757;	// L1147
    if (v758) {	// L1148
      raw = 1;	// L1149
    }
    int32_t v759 = fwd_a;	// L1151
    bool v760 = v759 == 1;	// L1152
    if (v760) {	// L1153
      int32_t v761 = fwd_a_ix;	// L1154
      int v762 = v761;	// L1155
      half v763 = resq[v762];	// L1156
      a = v763;	// L1157
      a_vld = 1;	// L1158
    }
    int32_t v764 = fwd_b;	// L1160
    bool v765 = v764 == 1;	// L1161
    if (v765) {	// L1162
      int32_t v766 = fwd_b_ix;	// L1163
      int v767 = v766;	// L1164
      half v768 = resq[v767];	// L1165
      b = v768;	// L1166
      b_vld = 1;	// L1167
    }
    int32_t is_cond;	// L1169
    is_cond = 0;	// L1170
    int32_t v770 = op;	// L1171
    bool v771 = v770 >= 12;	// L1172
    ap_int<33> v772 = v770;	// L1173
    bool v773 = v772 <= 15;	// L1174
    bool v774 = v771 & v773;	// L1175
    if (v774) {	// L1176
      is_cond = 1;	// L1177
    }
    int32_t grant;	// L1179
    grant = 0;	// L1180
    int32_t v776 = pc;	// L1181
    bool v777 = v776 >= 0;	// L1182
    if (v777) {	// L1183
      grant = 1;	// L1184
    }
    int32_t v778 = pc;	// L1186
    bool v779 = v778 >= 0;	// L1187
    int32_t v780 = a_vld;	// L1188
    bool v781 = v780 == 0;	// L1189
    int32_t v782 = binop;	// L1190
    bool v783 = v782 == 1;	// L1191
    int32_t v784 = b_vld;	// L1192
    bool v785 = v784 == 0;	// L1193
    bool v786 = v783 & v785;	// L1194
    bool v787 = v781 | v786;	// L1195
    bool v788 = v779 & v787;	// L1196
    if (v788) {	// L1197
      grant = 0;	// L1198
    }
    int32_t v789 = pc;	// L1200
    bool v790 = v789 >= 0;	// L1201
    int32_t v791 = raw;	// L1202
    bool v792 = v791 == 1;	// L1203
    int32_t v793 = is_cond;	// L1204
    bool v794 = v793 == 1;	// L1205
    int32_t v795 = cmp_busy;	// L1206
    bool v796 = v795 == 1;	// L1207
    bool v797 = v794 & v796;	// L1208
    bool v798 = v792 | v797;	// L1209
    bool v799 = v790 & v798;	// L1210
    if (v799) {	// L1211
      grant = 0;	// L1212
    }
    int32_t v800 = retire_ok;	// L1214
    bool v801 = v800 == 0;	// L1215
    if (v801) {	// L1216
      grant = 0;	// L1217
    }
    int32_t v802 = grant;	// L1219
    bool v803 = v802 == 1;	// L1220
    if (v803) {	// L1221
      int8_t v804 = instr_cnt;	// L1222
      int32_t v805 = cfg_isz;	// L1223
      int32_t v806 = v804;	// L1224
      bool v807 = v806 == v805;	// L1225
      if (v807) {	// L1226
        instr_cnt = 0;	// L1227
        int8_t v808 = iter_cnt;	// L1228
        int32_t v809 = cfg_itsz;	// L1229
        ap_int<33> v810 = v809;	// L1230
        ap_int<33> v811 = v810 - 1;	// L1231
        ap_int<33> v812 = v808;	// L1232
        bool v813 = v812 == v811;	// L1233
        if (v813) {	// L1234
          fetch_en = 0;	// L1235
        } else {
          int8_t v814 = iter_cnt;	// L1237
          ap_int<33> v815 = v814;	// L1238
          ap_int<33> v816 = v815 + 1;	// L1239
          uint8_t v817 = v816;	// L1240
          iter_cnt = v817;	// L1241
        }
      } else {
        int8_t v818 = instr_cnt;	// L1244
        ap_int<33> v819 = v818;	// L1245
        ap_int<33> v820 = v819 + 1;	// L1246
        uint8_t v821 = v820;	// L1247
        instr_cnt = v821;	// L1248
      }
    }
    int32_t c1;	// L1251
    c1 = -1;	// L1252
    int32_t c2;	// L1253
    c2 = -1;	// L1254
    int32_t v824 = grant;	// L1255
    bool v825 = v824 == 1;	// L1256
    int32_t v826 = s1;	// L1257
    bool v827 = v826 >= 12;	// L1258
    bool v828 = v825 & v827;	// L1259
    if (v828) {	// L1260
      int32_t v829 = s1;	// L1261
      int32_t v830 = v829 & 3;	// L1262
      c1 = v830;	// L1263
    }
    int32_t v831 = grant;	// L1265
    bool v832 = v831 == 1;	// L1266
    int32_t v833 = s2;	// L1267
    bool v834 = v833 >= 12;	// L1268
    bool v835 = v832 & v834;	// L1269
    if (v835) {	// L1270
      int32_t v836 = s2;	// L1271
      int32_t v837 = v836 & 3;	// L1272
      c2 = v837;	// L1273
    }
    int32_t v838 = c1;	// L1275
    bool v839 = v838 >= 0;	// L1276
    if (v839) {	// L1277
      int32_t v840 = c1;	// L1278
      int v841 = v840;	// L1279
      half v842 = hold_v[v841][1];	// L1280
      hold_v[v841][0] = v842;	// L1281
      int32_t v843 = c1;	// L1282
      int v844 = v843;	// L1283
      uint8_t v845 = hold_cnt[v844];	// L1284
      ap_int<33> v846 = v845;	// L1285
      ap_int<33> v847 = v846 - 1;	// L1286
      uint8_t v848 = v847;	// L1287
      hold_cnt[v844] = v848;	// L1288
    }
    int32_t v849 = c2;	// L1290
    bool v850 = v849 >= 0;	// L1291
    int32_t v851 = c1;	// L1292
    bool v852 = v849 != v851;	// L1293
    bool v853 = v850 & v852;	// L1294
    if (v853) {	// L1295
      int32_t v854 = c2;	// L1296
      int v855 = v854;	// L1297
      half v856 = hold_v[v855][1];	// L1298
      hold_v[v855][0] = v856;	// L1299
      int32_t v857 = c2;	// L1300
      int v858 = v857;	// L1301
      uint8_t v859 = hold_cnt[v858];	// L1302
      ap_int<33> v860 = v859;	// L1303
      ap_int<33> v861 = v860 - 1;	// L1304
      uint8_t v862 = v861;	// L1305
      hold_cnt[v858] = v862;	// L1306
    }
    l_S_d_7_d4: for (int d4 = 0; d4 < 4; d4++) {	// L1308
      sc_r[d4] = 0;	// L1309
    }
    int32_t v864 = c1;	// L1311
    bool v865 = v864 >= 0;	// L1312
    if (v865) {	// L1313
      int32_t v866 = c1;	// L1314
      int v867 = v866;	// L1315
      sc_r[v867] = 1;	// L1316
    }
    int32_t v868 = c2;	// L1318
    bool v869 = v868 >= 0;	// L1319
    int32_t v870 = c1;	// L1320
    bool v871 = v868 != v870;	// L1321
    bool v872 = v869 & v871;	// L1322
    if (v872) {	// L1323
      int32_t v873 = c2;	// L1324
      int v874 = v873;	// L1325
      sc_r[v874] = 1;	// L1326
    }
    int32_t v875 = grant;	// L1328
    bool v876 = v875 == 1;	// L1329
    int32_t v877 = s1;	// L1330
    bool v878 = v877 < 8;	// L1331
    int32_t v879 = dsmask;	// L1332
    int32_t v880 = v879 >> v877;	// L1333
    int32_t v881 = v880 & 1;	// L1334
    bool v882 = v881 == 1;	// L1335
    bool v883 = v876 & v878;	// L1336
    bool v884 = v883 & v882;	// L1337
    if (v884) {	// L1338
      int32_t v885 = s1;	// L1339
      int v886 = v885;	// L1340
      drf_full[v886] = 0;	// L1341
    }
    int32_t v887 = grant;	// L1343
    bool v888 = v887 == 1;	// L1344
    int32_t v889 = s2;	// L1345
    bool v890 = v889 < 8;	// L1346
    int32_t v891 = dsmask;	// L1347
    int32_t v892 = v891 >> v889;	// L1348
    int32_t v893 = v892 & 1;	// L1349
    bool v894 = v893 == 1;	// L1350
    bool v895 = v888 & v890;	// L1351
    bool v896 = v895 & v894;	// L1352
    if (v896) {	// L1353
      int32_t v897 = s2;	// L1354
      int v898 = v897;	// L1355
      drf_full[v898] = 0;	// L1356
    }
    half res;
#pragma HLS dependence variable=res type=inter dependent=false	// L1358
    res = (double)0.000000;	// L1359
    int32_t v900 = op;	// L1360
    bool v901 = v900 == 0;	// L1361
    if (v901) {	// L1362
      half v902 = a;	// L1363
      half v903 = b;	// L1364
      half v904 = v902 + v903;
#pragma HLS bind_op variable=v904 op=hadd impl=fabric latency=2	// L1365
      res = v904;	// L1366
    } else {
      int32_t v905 = op;	// L1368
      bool v906 = v905 == 1;	// L1369
      if (v906) {	// L1370
        half v907 = a;	// L1371
        half v908 = b;	// L1372
        half v909 = v907 - v908;
#pragma HLS bind_op variable=v909 op=hsub impl=fabric latency=2	// L1373
        res = v909;	// L1374
      } else {
        int32_t v910 = op;	// L1376
        bool v911 = v910 == 2;	// L1377
        if (v911) {	// L1378
          half v912 = a;	// L1379
          half v913 = b;	// L1380
          half v914 = v912 * v913;
#pragma HLS bind_op variable=v914 op=hmul impl=maxdsp latency=2	// L1381
          res = v914;	// L1382
        } else {
          int32_t v915 = op;	// L1384
          bool v916 = v915 == 8;	// L1385
          if (v916) {	// L1386
            half v917 = a;	// L1387
            half v918 = b;	// L1388
            bool v919 = v917 >= v918;	// L1389
            if (v919) {	// L1390
              res = (double)1.000000;	// L1391
            } else {
              res = (double)-1.000000;	// L1393
            }
          } else {
            int32_t v920 = op;	// L1396
            bool v921 = v920 == 9;	// L1397
            if (v921) {	// L1398
              half v922 = a;	// L1399
              half v923 = b;	// L1400
              bool v924 = v922 < v923;	// L1401
              if (v924) {	// L1402
                res = (double)1.000000;	// L1403
              } else {
                res = (double)-1.000000;	// L1405
              }
            } else {
              half v925 = a;	// L1408
              res = v925;	// L1409
            }
          }
        }
      }
    }
    int32_t v926 = a_vld;	// L1415
    int32_t res_vld;	// L1416
    res_vld = v926;	// L1417
    int32_t v928 = op;	// L1418
    bool v929 = v928 == 0;	// L1419
    bool v930 = v928 == 1;	// L1420
    bool v931 = v928 == 2;	// L1421
    bool v932 = v928 == 8;	// L1422
    bool v933 = v928 == 9;	// L1423
    bool v934 = v929 | v930;	// L1424
    bool v935 = v934 | v931;	// L1425
    bool v936 = v935 | v932;	// L1426
    bool v937 = v936 | v933;	// L1427
    if (v937) {	// L1428
      int32_t v938 = a_vld;	// L1429
      int32_t v939 = b_vld;	// L1430
      int64_t v940 = v938;	// L1431
      int64_t v941 = v939;	// L1432
      int64_t v942 = v940 * v941;	// L1433
      int32_t v943 = v942;	// L1434
      res_vld = v943;	// L1435
    }
    int32_t v944 = grant;	// L1437
    bool v945 = v944 == 0;	// L1438
    if (v945) {	// L1439
      res_vld = 0;	// L1440
    }
    int32_t is_rtr;	// L1442
    is_rtr = 0;	// L1443
    int32_t v947 = op;	// L1444
    bool v948 = v947 >= 4;	// L1445
    ap_int<33> v949 = v947;	// L1446
    bool v950 = v949 <= 7;	// L1447
    bool v951 = v948 & v950;	// L1448
    if (v951) {	// L1449
      is_rtr = 1;	// L1450
    }
    int32_t v952 = retire_ok;	// L1452
    bool v953 = v952 == 1;	// L1453
    if (v953) {	// L1454
      l_S_k_8_k1: for (int k1 = 0; k1 < 4; k1++) {	// L1455
        uint8_t v955 = sb_v[(k1 + 1)];	// L1456
        sb_v[k1] = v955;	// L1457
        uint8_t v956 = sb_dst[(k1 + 1)];	// L1458
        sb_dst[k1] = v956;	// L1459
        uint8_t v957 = sb_cmp[(k1 + 1)];	// L1460
        sb_cmp[k1] = v957;	// L1461
        uint8_t v958 = sb_rtr[(k1 + 1)];	// L1462
        sb_rtr[k1] = v958;	// L1463
        uint8_t v959 = sb_inj[(k1 + 1)];	// L1464
        sb_inj[k1] = v959;	// L1465
        uint8_t v960 = sb_dir[(k1 + 1)];	// L1466
        sb_dir[k1] = v960;	// L1467
        uint8_t v961 = sb_id[(k1 + 1)];	// L1468
        sb_id[k1] = v961;	// L1469
        uint8_t v962 = sb_rvld[(k1 + 1)];	// L1470
        sb_rvld[k1] = v962;	// L1471
        uint8_t v963 = sb_ix[(k1 + 1)];	// L1472
        sb_ix[k1] = v963;	// L1473
        uint8_t v964 = sb_long[(k1 + 1)];	// L1474
        sb_long[k1] = v964;	// L1475
      }
      sb_v[4] = 0;	// L1477
    }
    int32_t v965 = grant;	// L1479
    bool v966 = v965 == 1;	// L1480
    if (v966) {	// L1481
      half v967 = res;	// L1482
      int8_t v968 = resq_wr;	// L1483
      int v969 = v968;	// L1484
      resq[v969] = v967;	// L1485
      int32_t cq;	// L1486
      cq = 0;	// L1487
      int32_t v971 = op;	// L1488
      bool v972 = v971 == 8;	// L1489
      if (v972) {	// L1490
        half v973 = a;	// L1491
        half v974 = b;	// L1492
        bool v975 = v973 >= v974;	// L1493
        if (v975) {	// L1494
          cq = 1;	// L1495
        }
      }
      int32_t v976 = op;	// L1498
      bool v977 = v976 == 9;	// L1499
      if (v977) {	// L1500
        half v978 = a;	// L1501
        half v979 = b;	// L1502
        bool v980 = v978 < v979;	// L1503
        if (v980) {	// L1504
          cq = 1;	// L1505
        }
      }
      int32_t v981 = cq;	// L1508
      uint8_t v982 = v981;	// L1509
      int8_t v983 = resq_wr;	// L1510
      int v984 = v983;	// L1511
      cmpq[v984] = v982;	// L1512
      sb_v[4] = 1;	// L1513
      int32_t v985 = dst;	// L1514
      uint8_t v986 = v985;	// L1515
      sb_dst[4] = v986;	// L1516
      int8_t v987 = resq_wr;	// L1517
      sb_ix[4] = v987;	// L1518
      int32_t v988 = binop;	// L1519
      uint8_t v989 = v988;	// L1520
      sb_long[4] = v989;	// L1521
      sb_cmp[4] = 0;	// L1522
      int32_t v990 = op;	// L1523
      bool v991 = v990 == 8;	// L1524
      bool v992 = v990 == 9;	// L1525
      bool v993 = v991 | v992;	// L1526
      if (v993) {	// L1527
        sb_cmp[4] = 1;	// L1528
      }
      int32_t v994 = is_rtr;	// L1530
      int32_t rtrf;	// L1531
      rtrf = v994;	// L1532
      int32_t v996 = is_cond;	// L1533
      bool v997 = v996 == 1;	// L1534
      if (v997) {	// L1535
        rtrf = 1;	// L1536
      }
      int32_t v998 = rtrf;	// L1538
      uint8_t v999 = v998;	// L1539
      sb_rtr[4] = v999;	// L1540
      int32_t v1000 = is_rtr;	// L1541
      int32_t inj;	// L1542
      inj = v1000;	// L1543
      int32_t v1002 = is_cond;	// L1544
      bool v1003 = v1002 == 1;	// L1545
      int8_t v1004 = condition_reg;	// L1546
      int32_t v1005 = v1004;	// L1547
      bool v1006 = v1005 == 1;	// L1548
      bool v1007 = v1003 & v1006;	// L1549
      if (v1007) {	// L1550
        inj = 1;	// L1551
      }
      int32_t v1008 = inj;	// L1553
      uint8_t v1009 = v1008;	// L1554
      sb_inj[4] = v1009;	// L1555
      int32_t v1010 = op;	// L1556
      int32_t v1011 = v1010 & 3;	// L1557
      uint8_t v1012 = v1011;	// L1558
      sb_dir[4] = v1012;	// L1559
      int32_t v1013 = s2;	// L1560
      uint8_t v1014 = v1013;	// L1561
      sb_id[4] = v1014;	// L1562
      int32_t v1015 = res_vld;	// L1563
      uint8_t v1016 = v1015;	// L1564
      sb_rvld[4] = v1016;	// L1565
      int8_t v1017 = resq_wr;	// L1566
      ap_int<33> v1018 = v1017;	// L1567
      ap_int<33> v1019 = v1018 + 1;	// L1568
      ap_int<33> v1020 = v1019 & 7;	// L1569
      uint8_t v1021 = v1020;	// L1570
      resq_wr = v1021;	// L1571
    }
    txn_r = 0;	// L1573
    txs_r = 0;	// L1574
    txw_r = 0;	// L1575
    txe_r = 0;	// L1576
    int32_t v1022 = txp_v[0];	// L1577
    bool v1023 = v1022 == 1;	// L1578
    int32_t v1024 = scred[0];	// L1579
    bool v1025 = v1024 > 0;	// L1580
    bool v1026 = v1023 & v1025;	// L1581
    if (v1026) {	// L1582
      ap_uint<17> twn;	// L1583
      twn = 0;	// L1584
      ap_int<17> v1028 = twn;	// L1585
      ap_int<17> v1029;
      ap_int<17> v1029_tmp = v1028;
      v1029_tmp[0] = 1;      v1029 = v1029_tmp;	// L1586
      twn = v1029;	// L1587
      half v1030 = txp_d[0];	// L1588
      uint16_t v1031;
      union { half from; uint16_t to;} _converter_v1030_to_v1031 = {};
      _converter_v1030_to_v1031.from = v1030;
      v1031 = _converter_v1030_to_v1031.to;	// L1589
      ap_int<17> v1032 = twn;	// L1590
      ap_int<17> v1033;
      ap_int<17> v1033_tmp = v1032;
      v1033_tmp(16, 1) = v1031;
      v1033 = v1033_tmp;	// L1591
      twn = v1033;	// L1592
      ap_int<17> v1034 = twn;	// L1593
      txn_r = v1034;	// L1594
      txp_v[0] = 0;	// L1595
      int32_t v1035 = scred[0];	// L1596
      ap_int<33> v1036 = v1035;	// L1597
      ap_int<33> v1037 = v1036 - 1;	// L1598
      int32_t v1038 = v1037;	// L1599
      scred[0] = v1038;	// L1600
    }
    int32_t v1039 = txp_v[1];	// L1602
    bool v1040 = v1039 == 1;	// L1603
    int32_t v1041 = scred[1];	// L1604
    bool v1042 = v1041 > 0;	// L1605
    bool v1043 = v1040 & v1042;	// L1606
    if (v1043) {	// L1607
      ap_uint<17> tws;	// L1608
      tws = 0;	// L1609
      ap_int<17> v1045 = tws;	// L1610
      ap_int<17> v1046;
      ap_int<17> v1046_tmp = v1045;
      v1046_tmp[0] = 1;      v1046 = v1046_tmp;	// L1611
      tws = v1046;	// L1612
      half v1047 = txp_d[1];	// L1613
      uint16_t v1048;
      union { half from; uint16_t to;} _converter_v1047_to_v1048 = {};
      _converter_v1047_to_v1048.from = v1047;
      v1048 = _converter_v1047_to_v1048.to;	// L1614
      ap_int<17> v1049 = tws;	// L1615
      ap_int<17> v1050;
      ap_int<17> v1050_tmp = v1049;
      v1050_tmp(16, 1) = v1048;
      v1050 = v1050_tmp;	// L1616
      tws = v1050;	// L1617
      ap_int<17> v1051 = tws;	// L1618
      txs_r = v1051;	// L1619
      txp_v[1] = 0;	// L1620
      int32_t v1052 = scred[1];	// L1621
      ap_int<33> v1053 = v1052;	// L1622
      ap_int<33> v1054 = v1053 - 1;	// L1623
      int32_t v1055 = v1054;	// L1624
      scred[1] = v1055;	// L1625
    }
    int32_t v1056 = txp_v[2];	// L1627
    bool v1057 = v1056 == 1;	// L1628
    int32_t v1058 = scred[2];	// L1629
    bool v1059 = v1058 > 0;	// L1630
    bool v1060 = v1057 & v1059;	// L1631
    if (v1060) {	// L1632
      ap_uint<17> tww;	// L1633
      tww = 0;	// L1634
      ap_int<17> v1062 = tww;	// L1635
      ap_int<17> v1063;
      ap_int<17> v1063_tmp = v1062;
      v1063_tmp[0] = 1;      v1063 = v1063_tmp;	// L1636
      tww = v1063;	// L1637
      half v1064 = txp_d[2];	// L1638
      uint16_t v1065;
      union { half from; uint16_t to;} _converter_v1064_to_v1065 = {};
      _converter_v1064_to_v1065.from = v1064;
      v1065 = _converter_v1064_to_v1065.to;	// L1639
      ap_int<17> v1066 = tww;	// L1640
      ap_int<17> v1067;
      ap_int<17> v1067_tmp = v1066;
      v1067_tmp(16, 1) = v1065;
      v1067 = v1067_tmp;	// L1641
      tww = v1067;	// L1642
      ap_int<17> v1068 = tww;	// L1643
      txw_r = v1068;	// L1644
      txp_v[2] = 0;	// L1645
      int32_t v1069 = scred[2];	// L1646
      ap_int<33> v1070 = v1069;	// L1647
      ap_int<33> v1071 = v1070 - 1;	// L1648
      int32_t v1072 = v1071;	// L1649
      scred[2] = v1072;	// L1650
    }
    int32_t v1073 = txp_v[3];	// L1652
    bool v1074 = v1073 == 1;	// L1653
    int32_t v1075 = scred[3];	// L1654
    bool v1076 = v1075 > 0;	// L1655
    bool v1077 = v1074 & v1076;	// L1656
    if (v1077) {	// L1657
      ap_uint<17> twe;	// L1658
      twe = 0;	// L1659
      ap_int<17> v1079 = twe;	// L1660
      ap_int<17> v1080;
      ap_int<17> v1080_tmp = v1079;
      v1080_tmp[0] = 1;      v1080 = v1080_tmp;	// L1661
      twe = v1080;	// L1662
      half v1081 = txp_d[3];	// L1663
      uint16_t v1082;
      union { half from; uint16_t to;} _converter_v1081_to_v1082 = {};
      _converter_v1081_to_v1082.from = v1081;
      v1082 = _converter_v1081_to_v1082.to;	// L1664
      ap_int<17> v1083 = twe;	// L1665
      ap_int<17> v1084;
      ap_int<17> v1084_tmp = v1083;
      v1084_tmp(16, 1) = v1082;
      v1084 = v1084_tmp;	// L1666
      twe = v1084;	// L1667
      ap_int<17> v1085 = twe;	// L1668
      txe_r = v1085;	// L1669
      txp_v[3] = 0;	// L1670
      int32_t v1086 = scred[3];	// L1671
      ap_int<33> v1087 = v1086;	// L1672
      ap_int<33> v1088 = v1087 - 1;	// L1673
      int32_t v1089 = v1088;	// L1674
      scred[3] = v1089;	// L1675
    }
    int32_t v1090 = crv_vld;	// L1677
    bool v1091 = v1090 == 1;	// L1678
    if (v1091) {	// L1679
      int32_t v1092 = crv_mode;	// L1680
      bool v1093 = v1092 == 1;	// L1681
      if (v1093) {	// L1682
        int32_t v1094 = crv_addr;	// L1683
        int32_t v1095 = v1094 >> 3;	// L1684
        int32_t v1096 = v1095 & 1;	// L1685
        bool v1097 = v1096 == 1;	// L1686
        if (v1097) {	// L1687
          int32_t v1098 = crv_raw;	// L1688
          int32_t v1099 = crv_addr;	// L1689
          int32_t v1100 = v1099 & 7;	// L1690
          int v1101 = v1100;	// L1691
          irf[v1101] = v1098;	// L1692
        } else {
          int32_t v1102 = crv_addr;	// L1694
          bool v1103 = v1102 == 0;	// L1695
          if (v1103) {	// L1696
            int32_t v1104 = crv_raw;	// L1697
            int32_t v1105 = v1104 & 255;	// L1698
            dsmask = v1105;	// L1699
            int32_t v1106 = crv_raw;	// L1700
            int32_t v1107 = v1106 >> 8;	// L1701
            int32_t v1108 = v1107 & 7;	// L1702
            cfg_isz = v1108;	// L1703
            int32_t v1109 = crv_raw;	// L1704
            int32_t v1110 = v1109 >> 15;	// L1705
            int32_t v1111 = v1110 & 1;	// L1706
            bool v1112 = v1111 == 1;	// L1707
            if (v1112) {	// L1708
              fetch_en = 1;	// L1709
              instr_cnt = 0;	// L1710
              iter_cnt = 0;	// L1711
            }
          } else {
            int32_t v1113 = crv_addr;	// L1714
            bool v1114 = v1113 == 1;	// L1715
            if (v1114) {	// L1716
              int32_t v1115 = crv_raw;	// L1717
              int32_t v1116 = v1115 & 255;	// L1718
              cfg_itsz = v1116;	// L1719
            }
          }
        }
      } else {
        int32_t v1117 = crv_addr;	// L1724
        int32_t v1118 = v1117 >> 2;	// L1725
        int32_t v1119 = v1118 & 3;	// L1726
        bool v1120 = v1119 == 3;	// L1727
        if (v1120) {	// L1728
          int32_t v1121 = crv_addr;	// L1729
          int32_t v1122 = v1121 & 3;	// L1730
          int v1123 = v1122;	// L1731
          txp_v[v1123] = 1;	// L1732
          half v1124 = crv_data;	// L1733
          int32_t v1125 = crv_addr;	// L1734
          int32_t v1126 = v1125 & 3;	// L1735
          int v1127 = v1126;	// L1736
          txp_d[v1127] = v1124;	// L1737
          int32_t v1128 = crv_addr;	// L1738
          int32_t v1129 = v1128 & 3;	// L1739
          int v1130 = v1129;	// L1740
          txp_r[v1130] = 1;	// L1741
        } else {
          int32_t v1131 = crv_addr;	// L1743
          bool v1132 = v1131 < 8;	// L1744
          int32_t v1133 = dsmask;	// L1745
          int32_t v1134 = v1133 >> v1131;	// L1746
          int32_t v1135 = v1134 & 1;	// L1747
          bool v1136 = v1135 == 1;	// L1748
          bool v1137 = v1132 & v1136;	// L1749
          if (v1137) {	// L1750
            int32_t v1138 = crv_addr;	// L1751
            int v1139 = v1138;	// L1752
            int32_t v1140 = drf_full[v1139];	// L1753
            bool v1141 = v1140 == 0;	// L1754
            if (v1141) {	// L1755
              half v1142 = crv_data;	// L1756
              int32_t v1143 = crv_addr;	// L1757
              int v1144 = v1143;	// L1758
              drf[v1144] = v1142;	// L1759
              int32_t v1145 = crv_addr;	// L1760
              int v1146 = v1145;	// L1761
              drf_full[v1146] = 1;	// L1762
            }
          } else {
            half v1147 = crv_data;	// L1765
            int32_t v1148 = crv_addr;	// L1766
            int v1149 = v1148;	// L1767
            drf[v1149] = v1147;	// L1768
          }
        }
      }
    }
    ap_int<26> v1150 = oe_r;	// L1773
    v0.write(v1150);	// L1774
    ap_int<26> v1151 = ow_r;	// L1775
    v1.write(v1151);	// L1776
    ap_int<26> v1152 = os_r;	// L1777
    v2.write(v1152);	// L1778
    ap_int<26> v1153 = on_r;	// L1779
    v3.write(v1153);	// L1780
    ap_int<17> v1154 = txe_r;	// L1781
    v4.write(v1154);	// L1782
    ap_int<17> v1155 = txw_r;	// L1783
    v5.write(v1155);	// L1784
    ap_int<17> v1156 = txs_r;	// L1785
    v6.write(v1156);	// L1786
    ap_int<17> v1157 = txn_r;	// L1787
    v7.write(v1157);	// L1788
    int8_t v1158 = cre_r;	// L1789
    v8.write(v1158);	// L1790
    int8_t v1159 = crw_r;	// L1791
    v9.write(v1159);	// L1792
    int8_t v1160 = crs_r;	// L1793
    v10.write(v1160);	// L1794
    int8_t v1161 = crn_r;	// L1795
    v11.write(v1161);	// L1796
    int32_t v1162 = sc_r[0];	// L1797
    v14.write(v1162);	// L1798
    int32_t v1163 = sc_r[1];	// L1799
    v15.write(v1163);	// L1800
    int32_t v1164 = sc_r[2];	// L1801
    v12.write(v1164);	// L1802
    int32_t v1165 = sc_r[3];	// L1803
    v13.write(v1165);	// L1804
  }
}

void drv_w_0(
  half v1166[1][200],
  int32_t v1167[1][200],
  hls::stream< ap_uint<17> >& v1168,
  hls::stream< int32_t >& v1169
) {	// L1808
  int32_t dcred[1];	// L1817
  for (int v1171 = 0; v1171 < 1; v1171++) {	// L1818
    dcred[v1171] = 0;	// L1818
  }
  int32_t sp[1];	// L1819
  for (int v1173 = 0; v1173 < 1; v1173++) {	// L1820
    sp[v1173] = 0;	// L1820
  }
  ap_uint<17> zw;	// L1821
  zw = 0;	// L1822
  ap_int<17> v1175 = zw;	// L1823
  v1168.write(v1175);	// L1824
  ap_int<17> v1176 = zw;	// L1825
  v1168.write(v1176);	// L1826
  ap_int<17> v1177 = zw;	// L1827
  v1168.write(v1177);	// L1828
  ap_int<17> v1178 = zw;	// L1829
  v1168.write(v1178);	// L1830
  ap_int<17> v1179 = zw;	// L1831
  v1168.write(v1179);	// L1832
  l_S_t_0_t1: for (int t1 = 0; t1 < 200; t1++) {	// L1833
    int32_t v1181 = v1169.read();	// L1834
    int32_t v1182 = dcred[0];	// L1835
    ap_int<33> v1183 = v1182;	// L1836
    ap_int<33> v1184 = v1181;	// L1837
    ap_int<33> v1185 = v1183 + v1184;	// L1838
    int32_t v1186 = v1185;	// L1839
    dcred[0] = v1186;	// L1840
    ap_uint<17> w;	// L1841
    w = 0;	// L1842
    int32_t v1188 = sp[0];	// L1843
    bool v1189 = v1188 < 200;	// L1844
    ap_int<33> v1190 = t1;	// L1845
    ap_int<33> v1191 = v1188;	// L1846
    bool v1192 = v1190 >= v1191;	// L1847
    bool v1193 = v1189 & v1192;	// L1848
    if (v1193) {	// L1849
      int32_t v1194 = sp[0];	// L1850
      int v1195 = v1194;	// L1851
      int32_t v1196 = v1167[0][v1195];	// L1852
      bool v1197 = v1196 == 0;	// L1853
      if (v1197) {	// L1854
        int32_t v1198 = sp[0];	// L1855
        ap_int<33> v1199 = v1198;	// L1856
        ap_int<33> v1200 = v1199 + 1;	// L1857
        int32_t v1201 = v1200;	// L1858
        sp[0] = v1201;	// L1859
      } else {
        int32_t v1202 = dcred[0];	// L1861
        bool v1203 = v1202 > 0;	// L1862
        if (v1203) {	// L1863
          ap_int<17> v1204 = w;	// L1864
          ap_int<17> v1205;
          ap_int<17> v1205_tmp = v1204;
          v1205_tmp[0] = 1;          v1205 = v1205_tmp;	// L1865
          w = v1205;	// L1866
          int32_t v1206 = sp[0];	// L1867
          int v1207 = v1206;	// L1868
          half v1208 = v1166[0][v1207];	// L1869
          uint16_t v1209;
          union { half from; uint16_t to;} _converter_v1208_to_v1209 = {};
          _converter_v1208_to_v1209.from = v1208;
          v1209 = _converter_v1208_to_v1209.to;	// L1870
          ap_int<17> v1210 = w;	// L1871
          ap_int<17> v1211;
          ap_int<17> v1211_tmp = v1210;
          v1211_tmp(16, 1) = v1209;
          v1211 = v1211_tmp;	// L1872
          w = v1211;	// L1873
          int32_t v1212 = dcred[0];	// L1874
          ap_int<33> v1213 = v1212;	// L1875
          ap_int<33> v1214 = v1213 - 1;	// L1876
          int32_t v1215 = v1214;	// L1877
          dcred[0] = v1215;	// L1878
          int32_t v1216 = sp[0];	// L1879
          ap_int<33> v1217 = v1216;	// L1880
          ap_int<33> v1218 = v1217 + 1;	// L1881
          int32_t v1219 = v1218;	// L1882
          sp[0] = v1219;	// L1883
        }
      }
    }
    ap_int<17> v1220 = w;	// L1887
    v1168.write(v1220);	// L1888
  }
}

void drv_e_0(
  half v1221[1][200],
  int32_t v1222[1][200],
  hls::stream< ap_uint<17> >& v1223,
  hls::stream< int32_t >& v1224
) {	// L1892
  int32_t dcred1[1];	// L1901
  for (int v1226 = 0; v1226 < 1; v1226++) {	// L1902
    dcred1[v1226] = 0;	// L1902
  }
  int32_t sp1[1];	// L1903
  for (int v1228 = 0; v1228 < 1; v1228++) {	// L1904
    sp1[v1228] = 0;	// L1904
  }
  ap_uint<17> zw1;	// L1905
  zw1 = 0;	// L1906
  ap_int<17> v1230 = zw1;	// L1907
  v1223.write(v1230);	// L1908
  ap_int<17> v1231 = zw1;	// L1909
  v1223.write(v1231);	// L1910
  ap_int<17> v1232 = zw1;	// L1911
  v1223.write(v1232);	// L1912
  ap_int<17> v1233 = zw1;	// L1913
  v1223.write(v1233);	// L1914
  ap_int<17> v1234 = zw1;	// L1915
  v1223.write(v1234);	// L1916
  l_S_t_0_t2: for (int t2 = 0; t2 < 200; t2++) {	// L1917
    int32_t v1236 = v1224.read();	// L1918
    int32_t v1237 = dcred1[0];	// L1919
    ap_int<33> v1238 = v1237;	// L1920
    ap_int<33> v1239 = v1236;	// L1921
    ap_int<33> v1240 = v1238 + v1239;	// L1922
    int32_t v1241 = v1240;	// L1923
    dcred1[0] = v1241;	// L1924
    ap_uint<17> w1;	// L1925
    w1 = 0;	// L1926
    int32_t v1243 = sp1[0];	// L1927
    bool v1244 = v1243 < 200;	// L1928
    ap_int<33> v1245 = t2;	// L1929
    ap_int<33> v1246 = v1243;	// L1930
    bool v1247 = v1245 >= v1246;	// L1931
    bool v1248 = v1244 & v1247;	// L1932
    if (v1248) {	// L1933
      int32_t v1249 = sp1[0];	// L1934
      int v1250 = v1249;	// L1935
      int32_t v1251 = v1222[0][v1250];	// L1936
      bool v1252 = v1251 == 0;	// L1937
      if (v1252) {	// L1938
        int32_t v1253 = sp1[0];	// L1939
        ap_int<33> v1254 = v1253;	// L1940
        ap_int<33> v1255 = v1254 + 1;	// L1941
        int32_t v1256 = v1255;	// L1942
        sp1[0] = v1256;	// L1943
      } else {
        int32_t v1257 = dcred1[0];	// L1945
        bool v1258 = v1257 > 0;	// L1946
        if (v1258) {	// L1947
          ap_int<17> v1259 = w1;	// L1948
          ap_int<17> v1260;
          ap_int<17> v1260_tmp = v1259;
          v1260_tmp[0] = 1;          v1260 = v1260_tmp;	// L1949
          w1 = v1260;	// L1950
          int32_t v1261 = sp1[0];	// L1951
          int v1262 = v1261;	// L1952
          half v1263 = v1221[0][v1262];	// L1953
          uint16_t v1264;
          union { half from; uint16_t to;} _converter_v1263_to_v1264 = {};
          _converter_v1263_to_v1264.from = v1263;
          v1264 = _converter_v1263_to_v1264.to;	// L1954
          ap_int<17> v1265 = w1;	// L1955
          ap_int<17> v1266;
          ap_int<17> v1266_tmp = v1265;
          v1266_tmp(16, 1) = v1264;
          v1266 = v1266_tmp;	// L1956
          w1 = v1266;	// L1957
          int32_t v1267 = dcred1[0];	// L1958
          ap_int<33> v1268 = v1267;	// L1959
          ap_int<33> v1269 = v1268 - 1;	// L1960
          int32_t v1270 = v1269;	// L1961
          dcred1[0] = v1270;	// L1962
          int32_t v1271 = sp1[0];	// L1963
          ap_int<33> v1272 = v1271;	// L1964
          ap_int<33> v1273 = v1272 + 1;	// L1965
          int32_t v1274 = v1273;	// L1966
          sp1[0] = v1274;	// L1967
        }
      }
    }
    ap_int<17> v1275 = w1;	// L1971
    v1223.write(v1275);	// L1972
  }
}

void drv_n_0(
  half v1276[1][200],
  int32_t v1277[1][200],
  hls::stream< ap_uint<17> >& v1278,
  hls::stream< int32_t >& v1279
) {	// L1976
  int32_t dcred2[1];	// L1985
  for (int v1281 = 0; v1281 < 1; v1281++) {	// L1986
    dcred2[v1281] = 0;	// L1986
  }
  int32_t sp2[1];	// L1987
  for (int v1283 = 0; v1283 < 1; v1283++) {	// L1988
    sp2[v1283] = 0;	// L1988
  }
  ap_uint<17> zw2;	// L1989
  zw2 = 0;	// L1990
  ap_int<17> v1285 = zw2;	// L1991
  v1278.write(v1285);	// L1992
  ap_int<17> v1286 = zw2;	// L1993
  v1278.write(v1286);	// L1994
  ap_int<17> v1287 = zw2;	// L1995
  v1278.write(v1287);	// L1996
  ap_int<17> v1288 = zw2;	// L1997
  v1278.write(v1288);	// L1998
  ap_int<17> v1289 = zw2;	// L1999
  v1278.write(v1289);	// L2000
  l_S_t_0_t3: for (int t3 = 0; t3 < 200; t3++) {	// L2001
    int32_t v1291 = v1279.read();	// L2002
    int32_t v1292 = dcred2[0];	// L2003
    ap_int<33> v1293 = v1292;	// L2004
    ap_int<33> v1294 = v1291;	// L2005
    ap_int<33> v1295 = v1293 + v1294;	// L2006
    int32_t v1296 = v1295;	// L2007
    dcred2[0] = v1296;	// L2008
    ap_uint<17> w2;	// L2009
    w2 = 0;	// L2010
    int32_t v1298 = sp2[0];	// L2011
    bool v1299 = v1298 < 200;	// L2012
    ap_int<33> v1300 = t3;	// L2013
    ap_int<33> v1301 = v1298;	// L2014
    bool v1302 = v1300 >= v1301;	// L2015
    bool v1303 = v1299 & v1302;	// L2016
    if (v1303) {	// L2017
      int32_t v1304 = sp2[0];	// L2018
      int v1305 = v1304;	// L2019
      int32_t v1306 = v1277[0][v1305];	// L2020
      bool v1307 = v1306 == 0;	// L2021
      if (v1307) {	// L2022
        int32_t v1308 = sp2[0];	// L2023
        ap_int<33> v1309 = v1308;	// L2024
        ap_int<33> v1310 = v1309 + 1;	// L2025
        int32_t v1311 = v1310;	// L2026
        sp2[0] = v1311;	// L2027
      } else {
        int32_t v1312 = dcred2[0];	// L2029
        bool v1313 = v1312 > 0;	// L2030
        if (v1313) {	// L2031
          ap_int<17> v1314 = w2;	// L2032
          ap_int<17> v1315;
          ap_int<17> v1315_tmp = v1314;
          v1315_tmp[0] = 1;          v1315 = v1315_tmp;	// L2033
          w2 = v1315;	// L2034
          int32_t v1316 = sp2[0];	// L2035
          int v1317 = v1316;	// L2036
          half v1318 = v1276[0][v1317];	// L2037
          uint16_t v1319;
          union { half from; uint16_t to;} _converter_v1318_to_v1319 = {};
          _converter_v1318_to_v1319.from = v1318;
          v1319 = _converter_v1318_to_v1319.to;	// L2038
          ap_int<17> v1320 = w2;	// L2039
          ap_int<17> v1321;
          ap_int<17> v1321_tmp = v1320;
          v1321_tmp(16, 1) = v1319;
          v1321 = v1321_tmp;	// L2040
          w2 = v1321;	// L2041
          int32_t v1322 = dcred2[0];	// L2042
          ap_int<33> v1323 = v1322;	// L2043
          ap_int<33> v1324 = v1323 - 1;	// L2044
          int32_t v1325 = v1324;	// L2045
          dcred2[0] = v1325;	// L2046
          int32_t v1326 = sp2[0];	// L2047
          ap_int<33> v1327 = v1326;	// L2048
          ap_int<33> v1328 = v1327 + 1;	// L2049
          int32_t v1329 = v1328;	// L2050
          sp2[0] = v1329;	// L2051
        }
      }
    }
    ap_int<17> v1330 = w2;	// L2055
    v1278.write(v1330);	// L2056
  }
}

void drv_s_0(
  half v1331[1][200],
  int32_t v1332[1][200],
  hls::stream< ap_uint<17> >& v1333,
  hls::stream< int32_t >& v1334
) {	// L2060
  int32_t dcred3[1];	// L2069
  for (int v1336 = 0; v1336 < 1; v1336++) {	// L2070
    dcred3[v1336] = 0;	// L2070
  }
  int32_t sp3[1];	// L2071
  for (int v1338 = 0; v1338 < 1; v1338++) {	// L2072
    sp3[v1338] = 0;	// L2072
  }
  ap_uint<17> zw3;	// L2073
  zw3 = 0;	// L2074
  ap_int<17> v1340 = zw3;	// L2075
  v1333.write(v1340);	// L2076
  ap_int<17> v1341 = zw3;	// L2077
  v1333.write(v1341);	// L2078
  ap_int<17> v1342 = zw3;	// L2079
  v1333.write(v1342);	// L2080
  ap_int<17> v1343 = zw3;	// L2081
  v1333.write(v1343);	// L2082
  ap_int<17> v1344 = zw3;	// L2083
  v1333.write(v1344);	// L2084
  l_S_t_0_t4: for (int t4 = 0; t4 < 200; t4++) {	// L2085
    int32_t v1346 = v1334.read();	// L2086
    int32_t v1347 = dcred3[0];	// L2087
    ap_int<33> v1348 = v1347;	// L2088
    ap_int<33> v1349 = v1346;	// L2089
    ap_int<33> v1350 = v1348 + v1349;	// L2090
    int32_t v1351 = v1350;	// L2091
    dcred3[0] = v1351;	// L2092
    ap_uint<17> w3;	// L2093
    w3 = 0;	// L2094
    int32_t v1353 = sp3[0];	// L2095
    bool v1354 = v1353 < 200;	// L2096
    ap_int<33> v1355 = t4;	// L2097
    ap_int<33> v1356 = v1353;	// L2098
    bool v1357 = v1355 >= v1356;	// L2099
    bool v1358 = v1354 & v1357;	// L2100
    if (v1358) {	// L2101
      int32_t v1359 = sp3[0];	// L2102
      int v1360 = v1359;	// L2103
      int32_t v1361 = v1332[0][v1360];	// L2104
      bool v1362 = v1361 == 0;	// L2105
      if (v1362) {	// L2106
        int32_t v1363 = sp3[0];	// L2107
        ap_int<33> v1364 = v1363;	// L2108
        ap_int<33> v1365 = v1364 + 1;	// L2109
        int32_t v1366 = v1365;	// L2110
        sp3[0] = v1366;	// L2111
      } else {
        int32_t v1367 = dcred3[0];	// L2113
        bool v1368 = v1367 > 0;	// L2114
        if (v1368) {	// L2115
          ap_int<17> v1369 = w3;	// L2116
          ap_int<17> v1370;
          ap_int<17> v1370_tmp = v1369;
          v1370_tmp[0] = 1;          v1370 = v1370_tmp;	// L2117
          w3 = v1370;	// L2118
          int32_t v1371 = sp3[0];	// L2119
          int v1372 = v1371;	// L2120
          half v1373 = v1331[0][v1372];	// L2121
          uint16_t v1374;
          union { half from; uint16_t to;} _converter_v1373_to_v1374 = {};
          _converter_v1373_to_v1374.from = v1373;
          v1374 = _converter_v1373_to_v1374.to;	// L2122
          ap_int<17> v1375 = w3;	// L2123
          ap_int<17> v1376;
          ap_int<17> v1376_tmp = v1375;
          v1376_tmp(16, 1) = v1374;
          v1376 = v1376_tmp;	// L2124
          w3 = v1376;	// L2125
          int32_t v1377 = dcred3[0];	// L2126
          ap_int<33> v1378 = v1377;	// L2127
          ap_int<33> v1379 = v1378 - 1;	// L2128
          int32_t v1380 = v1379;	// L2129
          dcred3[0] = v1380;	// L2130
          int32_t v1381 = sp3[0];	// L2131
          ap_int<33> v1382 = v1381;	// L2132
          ap_int<33> v1383 = v1382 + 1;	// L2133
          int32_t v1384 = v1383;	// L2134
          sp3[0] = v1384;	// L2135
        }
      }
    }
    ap_int<17> v1385 = w3;	// L2139
    v1333.write(v1385);	// L2140
  }
}

void col_w_0(
  half v1386[1][200],
  hls::stream< int32_t >& v1387,
  hls::stream< ap_uint<17> >& v1388
) {	// L2144
  int32_t k2[1];	// L2153
  for (int v1390 = 0; v1390 < 1; v1390++) {	// L2154
    k2[v1390] = 0;	// L2154
  }
  int32_t cret[1];	// L2155
  for (int v1392 = 0; v1392 < 1; v1392++) {	// L2156
    cret[v1392] = 0;	// L2156
  }
  int32_t zc;	// L2157
  zc = 0;	// L2158
  int32_t v1394 = zc;	// L2159
  v1387.write(v1394);	// L2160
  int32_t v1395 = zc;	// L2161
  v1387.write(v1395);	// L2162
  int32_t v1396 = zc;	// L2163
  v1387.write(v1396);	// L2164
  int32_t v1397 = zc;	// L2165
  v1387.write(v1397);	// L2166
  int32_t v1398 = zc;	// L2167
  v1387.write(v1398);	// L2168
  cret[0] = 2;	// L2169
  int32_t v1399 = cret[0];	// L2170
  v1387.write(v1399);	// L2171
  l_S_t_0_t5: for (int t5 = 0; t5 < 200; t5++) {	// L2172
    ap_uint<17> v1401 = v1388.read();	// L2173
    ap_uint<17> w4;	// L2174
    w4 = v1401;	// L2175
    cret[0] = 0;	// L2176
    ap_int<17> v1403 = w4;	// L2177
    bool v1404;
    ap_int<17> v1404_tmp = v1403;
    v1404 = v1404_tmp[0];	// L2178
    int32_t v1405 = v1404;	// L2179
    bool v1406 = v1405 == 1;	// L2180
    if (v1406) {	// L2181
      cret[0] = 1;	// L2182
      int32_t v1407 = k2[0];	// L2183
      bool v1408 = v1407 < 200;	// L2184
      if (v1408) {	// L2185
        ap_int<17> v1409 = w4;	// L2186
        int16_t v1410;
        ap_int<17> v1410_tmp = v1409;
        v1410 = v1410_tmp(16, 1);	// L2187
        half v1411;
        union { uint16_t from; half to;} _converter_v1410_to_v1411 = {};
        _converter_v1410_to_v1411.from = v1410;
        v1411 = _converter_v1410_to_v1411.to;	// L2188
        int32_t v1412 = k2[0];	// L2189
        int v1413 = v1412;	// L2190
        v1386[0][v1413] = v1411;	// L2191
        int32_t v1414 = k2[0];	// L2192
        ap_int<33> v1415 = v1414;	// L2193
        ap_int<33> v1416 = v1415 + 1;	// L2194
        int32_t v1417 = v1416;	// L2195
        k2[0] = v1417;	// L2196
      }
    }
    int32_t v1418 = cret[0];	// L2199
    v1387.write(v1418);	// L2200
  }
}

void col_e_0(
  half v1419[1][200],
  hls::stream< int32_t >& v1420,
  hls::stream< ap_uint<17> >& v1421
) {	// L2204
  int32_t k3[1];	// L2213
  for (int v1423 = 0; v1423 < 1; v1423++) {	// L2214
    k3[v1423] = 0;	// L2214
  }
  int32_t cret1[1];	// L2215
  for (int v1425 = 0; v1425 < 1; v1425++) {	// L2216
    cret1[v1425] = 0;	// L2216
  }
  int32_t zc1;	// L2217
  zc1 = 0;	// L2218
  int32_t v1427 = zc1;	// L2219
  v1420.write(v1427);	// L2220
  int32_t v1428 = zc1;	// L2221
  v1420.write(v1428);	// L2222
  int32_t v1429 = zc1;	// L2223
  v1420.write(v1429);	// L2224
  int32_t v1430 = zc1;	// L2225
  v1420.write(v1430);	// L2226
  int32_t v1431 = zc1;	// L2227
  v1420.write(v1431);	// L2228
  cret1[0] = 2;	// L2229
  int32_t v1432 = cret1[0];	// L2230
  v1420.write(v1432);	// L2231
  l_S_t_0_t6: for (int t6 = 0; t6 < 200; t6++) {	// L2232
    ap_uint<17> v1434 = v1421.read();	// L2233
    ap_uint<17> w5;	// L2234
    w5 = v1434;	// L2235
    cret1[0] = 0;	// L2236
    ap_int<17> v1436 = w5;	// L2237
    bool v1437;
    ap_int<17> v1437_tmp = v1436;
    v1437 = v1437_tmp[0];	// L2238
    int32_t v1438 = v1437;	// L2239
    bool v1439 = v1438 == 1;	// L2240
    if (v1439) {	// L2241
      cret1[0] = 1;	// L2242
      int32_t v1440 = k3[0];	// L2243
      bool v1441 = v1440 < 200;	// L2244
      if (v1441) {	// L2245
        ap_int<17> v1442 = w5;	// L2246
        int16_t v1443;
        ap_int<17> v1443_tmp = v1442;
        v1443 = v1443_tmp(16, 1);	// L2247
        half v1444;
        union { uint16_t from; half to;} _converter_v1443_to_v1444 = {};
        _converter_v1443_to_v1444.from = v1443;
        v1444 = _converter_v1443_to_v1444.to;	// L2248
        int32_t v1445 = k3[0];	// L2249
        int v1446 = v1445;	// L2250
        v1419[0][v1446] = v1444;	// L2251
        int32_t v1447 = k3[0];	// L2252
        ap_int<33> v1448 = v1447;	// L2253
        ap_int<33> v1449 = v1448 + 1;	// L2254
        int32_t v1450 = v1449;	// L2255
        k3[0] = v1450;	// L2256
      }
    }
    int32_t v1451 = cret1[0];	// L2259
    v1420.write(v1451);	// L2260
  }
}

void col_n_0(
  half v1452[1][200],
  hls::stream< int32_t >& v1453,
  hls::stream< ap_uint<17> >& v1454
) {	// L2264
  int32_t k4[1];	// L2273
  for (int v1456 = 0; v1456 < 1; v1456++) {	// L2274
    k4[v1456] = 0;	// L2274
  }
  int32_t cret2[1];	// L2275
  for (int v1458 = 0; v1458 < 1; v1458++) {	// L2276
    cret2[v1458] = 0;	// L2276
  }
  int32_t zc2;	// L2277
  zc2 = 0;	// L2278
  int32_t v1460 = zc2;	// L2279
  v1453.write(v1460);	// L2280
  int32_t v1461 = zc2;	// L2281
  v1453.write(v1461);	// L2282
  int32_t v1462 = zc2;	// L2283
  v1453.write(v1462);	// L2284
  int32_t v1463 = zc2;	// L2285
  v1453.write(v1463);	// L2286
  int32_t v1464 = zc2;	// L2287
  v1453.write(v1464);	// L2288
  cret2[0] = 2;	// L2289
  int32_t v1465 = cret2[0];	// L2290
  v1453.write(v1465);	// L2291
  l_S_t_0_t7: for (int t7 = 0; t7 < 200; t7++) {	// L2292
    ap_uint<17> v1467 = v1454.read();	// L2293
    ap_uint<17> w6;	// L2294
    w6 = v1467;	// L2295
    cret2[0] = 0;	// L2296
    ap_int<17> v1469 = w6;	// L2297
    bool v1470;
    ap_int<17> v1470_tmp = v1469;
    v1470 = v1470_tmp[0];	// L2298
    int32_t v1471 = v1470;	// L2299
    bool v1472 = v1471 == 1;	// L2300
    if (v1472) {	// L2301
      cret2[0] = 1;	// L2302
      int32_t v1473 = k4[0];	// L2303
      bool v1474 = v1473 < 200;	// L2304
      if (v1474) {	// L2305
        ap_int<17> v1475 = w6;	// L2306
        int16_t v1476;
        ap_int<17> v1476_tmp = v1475;
        v1476 = v1476_tmp(16, 1);	// L2307
        half v1477;
        union { uint16_t from; half to;} _converter_v1476_to_v1477 = {};
        _converter_v1476_to_v1477.from = v1476;
        v1477 = _converter_v1476_to_v1477.to;	// L2308
        int32_t v1478 = k4[0];	// L2309
        int v1479 = v1478;	// L2310
        v1452[0][v1479] = v1477;	// L2311
        int32_t v1480 = k4[0];	// L2312
        ap_int<33> v1481 = v1480;	// L2313
        ap_int<33> v1482 = v1481 + 1;	// L2314
        int32_t v1483 = v1482;	// L2315
        k4[0] = v1483;	// L2316
      }
    }
    int32_t v1484 = cret2[0];	// L2319
    v1453.write(v1484);	// L2320
  }
}

void col_s_0(
  half v1485[1][200],
  hls::stream< int32_t >& v1486,
  hls::stream< ap_uint<17> >& v1487
) {	// L2324
  int32_t k5[1];	// L2333
  for (int v1489 = 0; v1489 < 1; v1489++) {	// L2334
    k5[v1489] = 0;	// L2334
  }
  int32_t cret3[1];	// L2335
  for (int v1491 = 0; v1491 < 1; v1491++) {	// L2336
    cret3[v1491] = 0;	// L2336
  }
  int32_t zc3;	// L2337
  zc3 = 0;	// L2338
  int32_t v1493 = zc3;	// L2339
  v1486.write(v1493);	// L2340
  int32_t v1494 = zc3;	// L2341
  v1486.write(v1494);	// L2342
  int32_t v1495 = zc3;	// L2343
  v1486.write(v1495);	// L2344
  int32_t v1496 = zc3;	// L2345
  v1486.write(v1496);	// L2346
  int32_t v1497 = zc3;	// L2347
  v1486.write(v1497);	// L2348
  cret3[0] = 2;	// L2349
  int32_t v1498 = cret3[0];	// L2350
  v1486.write(v1498);	// L2351
  l_S_t_0_t8: for (int t8 = 0; t8 < 200; t8++) {	// L2352
    ap_uint<17> v1500 = v1487.read();	// L2353
    ap_uint<17> w7;	// L2354
    w7 = v1500;	// L2355
    cret3[0] = 0;	// L2356
    ap_int<17> v1502 = w7;	// L2357
    bool v1503;
    ap_int<17> v1503_tmp = v1502;
    v1503 = v1503_tmp[0];	// L2358
    int32_t v1504 = v1503;	// L2359
    bool v1505 = v1504 == 1;	// L2360
    if (v1505) {	// L2361
      cret3[0] = 1;	// L2362
      int32_t v1506 = k5[0];	// L2363
      bool v1507 = v1506 < 200;	// L2364
      if (v1507) {	// L2365
        ap_int<17> v1508 = w7;	// L2366
        int16_t v1509;
        ap_int<17> v1509_tmp = v1508;
        v1509 = v1509_tmp(16, 1);	// L2367
        half v1510;
        union { uint16_t from; half to;} _converter_v1509_to_v1510 = {};
        _converter_v1509_to_v1510.from = v1509;
        v1510 = _converter_v1509_to_v1510.to;	// L2368
        int32_t v1511 = k5[0];	// L2369
        int v1512 = v1511;	// L2370
        v1485[0][v1512] = v1510;	// L2371
        int32_t v1513 = k5[0];	// L2372
        ap_int<33> v1514 = v1513;	// L2373
        ap_int<33> v1515 = v1514 + 1;	// L2374
        int32_t v1516 = v1515;	// L2375
        k5[0] = v1516;	// L2376
      }
    }
    int32_t v1517 = cret3[0];	// L2379
    v1486.write(v1517);	// L2380
  }
}

void rdrv_w_0(
  int32_t v1518[1][200],
  hls::stream< ap_uint<26> >& v1519,
  hls::stream< int32_t >& v1520
) {	// L2384
  int32_t dcred4[1];	// L2391
  for (int v1522 = 0; v1522 < 1; v1522++) {	// L2392
    dcred4[v1522] = 0;	// L2392
  }
  int32_t sp4[1];	// L2393
  for (int v1524 = 0; v1524 < 1; v1524++) {	// L2394
    sp4[v1524] = 0;	// L2394
  }
  ap_uint<26> zp;	// L2395
  zp = 0;	// L2396
  ap_int<26> v1526 = zp;	// L2397
  v1519.write(v1526);	// L2398
  ap_int<26> v1527 = zp;	// L2399
  v1519.write(v1527);	// L2400
  ap_int<26> v1528 = zp;	// L2401
  v1519.write(v1528);	// L2402
  ap_int<26> v1529 = zp;	// L2403
  v1519.write(v1529);	// L2404
  ap_int<26> v1530 = zp;	// L2405
  v1519.write(v1530);	// L2406
  l_S_t_0_t9: for (int t9 = 0; t9 < 200; t9++) {	// L2407
    int32_t v1532 = v1520.read();	// L2408
    int32_t v1533 = dcred4[0];	// L2409
    ap_int<33> v1534 = v1533;	// L2410
    ap_int<33> v1535 = v1532;	// L2411
    ap_int<33> v1536 = v1534 + v1535;	// L2412
    int32_t v1537 = v1536;	// L2413
    dcred4[0] = v1537;	// L2414
    ap_uint<26> pw;	// L2415
    pw = 0;	// L2416
    int32_t v1539 = sp4[0];	// L2417
    bool v1540 = v1539 < 200;	// L2418
    if (v1540) {	// L2419
      ap_uint<26> cand;	// L2420
      cand = 0;	// L2421
      int32_t v1542 = sp4[0];	// L2422
      int v1543 = v1542;	// L2423
      int32_t v1544 = v1518[0][v1543];	// L2424
      ap_uint<26> v1545 = v1544;	// L2425
      ap_int<26> v1546 = cand;	// L2426
      ap_int<26> v1547;
      ap_int<26> v1547_tmp = v1546;
      v1547_tmp(25, 0) = v1545;
      v1547 = v1547_tmp;	// L2427
      cand = v1547;	// L2428
      ap_int<26> v1548 = cand;	// L2429
      bool v1549;
      ap_int<26> v1549_tmp = v1548;
      v1549 = v1549_tmp[25];	// L2430
      int32_t v1550 = v1549;	// L2431
      bool v1551 = v1550 == 0;	// L2432
      if (v1551) {	// L2433
        int32_t v1552 = sp4[0];	// L2434
        ap_int<33> v1553 = v1552;	// L2435
        ap_int<33> v1554 = v1553 + 1;	// L2436
        int32_t v1555 = v1554;	// L2437
        sp4[0] = v1555;	// L2438
      } else {
        int32_t v1556 = dcred4[0];	// L2440
        bool v1557 = v1556 > 0;	// L2441
        if (v1557) {	// L2442
          ap_int<26> v1558 = cand;	// L2443
          pw = v1558;	// L2444
          int32_t v1559 = dcred4[0];	// L2445
          ap_int<33> v1560 = v1559;	// L2446
          ap_int<33> v1561 = v1560 - 1;	// L2447
          int32_t v1562 = v1561;	// L2448
          dcred4[0] = v1562;	// L2449
          int32_t v1563 = sp4[0];	// L2450
          ap_int<33> v1564 = v1563;	// L2451
          ap_int<33> v1565 = v1564 + 1;	// L2452
          int32_t v1566 = v1565;	// L2453
          sp4[0] = v1566;	// L2454
        }
      }
    }
    ap_int<26> v1567 = pw;	// L2458
    v1519.write(v1567);	// L2459
  }
}

void rdrv_e_0(
  int32_t v1568[1][200],
  hls::stream< ap_uint<26> >& v1569,
  hls::stream< int32_t >& v1570
) {	// L2463
  int32_t dcred5[1];	// L2470
  for (int v1572 = 0; v1572 < 1; v1572++) {	// L2471
    dcred5[v1572] = 0;	// L2471
  }
  int32_t sp5[1];	// L2472
  for (int v1574 = 0; v1574 < 1; v1574++) {	// L2473
    sp5[v1574] = 0;	// L2473
  }
  ap_uint<26> zp1;	// L2474
  zp1 = 0;	// L2475
  ap_int<26> v1576 = zp1;	// L2476
  v1569.write(v1576);	// L2477
  ap_int<26> v1577 = zp1;	// L2478
  v1569.write(v1577);	// L2479
  ap_int<26> v1578 = zp1;	// L2480
  v1569.write(v1578);	// L2481
  ap_int<26> v1579 = zp1;	// L2482
  v1569.write(v1579);	// L2483
  ap_int<26> v1580 = zp1;	// L2484
  v1569.write(v1580);	// L2485
  l_S_t_0_t10: for (int t10 = 0; t10 < 200; t10++) {	// L2486
    int32_t v1582 = v1570.read();	// L2487
    int32_t v1583 = dcred5[0];	// L2488
    ap_int<33> v1584 = v1583;	// L2489
    ap_int<33> v1585 = v1582;	// L2490
    ap_int<33> v1586 = v1584 + v1585;	// L2491
    int32_t v1587 = v1586;	// L2492
    dcred5[0] = v1587;	// L2493
    ap_uint<26> pw1;	// L2494
    pw1 = 0;	// L2495
    int32_t v1589 = sp5[0];	// L2496
    bool v1590 = v1589 < 200;	// L2497
    if (v1590) {	// L2498
      ap_uint<26> cand1;	// L2499
      cand1 = 0;	// L2500
      int32_t v1592 = sp5[0];	// L2501
      int v1593 = v1592;	// L2502
      int32_t v1594 = v1568[0][v1593];	// L2503
      ap_uint<26> v1595 = v1594;	// L2504
      ap_int<26> v1596 = cand1;	// L2505
      ap_int<26> v1597;
      ap_int<26> v1597_tmp = v1596;
      v1597_tmp(25, 0) = v1595;
      v1597 = v1597_tmp;	// L2506
      cand1 = v1597;	// L2507
      ap_int<26> v1598 = cand1;	// L2508
      bool v1599;
      ap_int<26> v1599_tmp = v1598;
      v1599 = v1599_tmp[25];	// L2509
      int32_t v1600 = v1599;	// L2510
      bool v1601 = v1600 == 0;	// L2511
      if (v1601) {	// L2512
        int32_t v1602 = sp5[0];	// L2513
        ap_int<33> v1603 = v1602;	// L2514
        ap_int<33> v1604 = v1603 + 1;	// L2515
        int32_t v1605 = v1604;	// L2516
        sp5[0] = v1605;	// L2517
      } else {
        int32_t v1606 = dcred5[0];	// L2519
        bool v1607 = v1606 > 0;	// L2520
        if (v1607) {	// L2521
          ap_int<26> v1608 = cand1;	// L2522
          pw1 = v1608;	// L2523
          int32_t v1609 = dcred5[0];	// L2524
          ap_int<33> v1610 = v1609;	// L2525
          ap_int<33> v1611 = v1610 - 1;	// L2526
          int32_t v1612 = v1611;	// L2527
          dcred5[0] = v1612;	// L2528
          int32_t v1613 = sp5[0];	// L2529
          ap_int<33> v1614 = v1613;	// L2530
          ap_int<33> v1615 = v1614 + 1;	// L2531
          int32_t v1616 = v1615;	// L2532
          sp5[0] = v1616;	// L2533
        }
      }
    }
    ap_int<26> v1617 = pw1;	// L2537
    v1569.write(v1617);	// L2538
  }
}

void rdrv_n_0(
  int32_t v1618[1][200],
  hls::stream< ap_uint<26> >& v1619,
  hls::stream< int32_t >& v1620
) {	// L2542
  int32_t dcred6[1];	// L2549
  for (int v1622 = 0; v1622 < 1; v1622++) {	// L2550
    dcred6[v1622] = 0;	// L2550
  }
  int32_t sp6[1];	// L2551
  for (int v1624 = 0; v1624 < 1; v1624++) {	// L2552
    sp6[v1624] = 0;	// L2552
  }
  ap_uint<26> zp2;	// L2553
  zp2 = 0;	// L2554
  ap_int<26> v1626 = zp2;	// L2555
  v1619.write(v1626);	// L2556
  ap_int<26> v1627 = zp2;	// L2557
  v1619.write(v1627);	// L2558
  ap_int<26> v1628 = zp2;	// L2559
  v1619.write(v1628);	// L2560
  ap_int<26> v1629 = zp2;	// L2561
  v1619.write(v1629);	// L2562
  ap_int<26> v1630 = zp2;	// L2563
  v1619.write(v1630);	// L2564
  l_S_t_0_t11: for (int t11 = 0; t11 < 200; t11++) {	// L2565
    int32_t v1632 = v1620.read();	// L2566
    int32_t v1633 = dcred6[0];	// L2567
    ap_int<33> v1634 = v1633;	// L2568
    ap_int<33> v1635 = v1632;	// L2569
    ap_int<33> v1636 = v1634 + v1635;	// L2570
    int32_t v1637 = v1636;	// L2571
    dcred6[0] = v1637;	// L2572
    ap_uint<26> pw2;	// L2573
    pw2 = 0;	// L2574
    int32_t v1639 = sp6[0];	// L2575
    bool v1640 = v1639 < 200;	// L2576
    if (v1640) {	// L2577
      ap_uint<26> cand2;	// L2578
      cand2 = 0;	// L2579
      int32_t v1642 = sp6[0];	// L2580
      int v1643 = v1642;	// L2581
      int32_t v1644 = v1618[0][v1643];	// L2582
      ap_uint<26> v1645 = v1644;	// L2583
      ap_int<26> v1646 = cand2;	// L2584
      ap_int<26> v1647;
      ap_int<26> v1647_tmp = v1646;
      v1647_tmp(25, 0) = v1645;
      v1647 = v1647_tmp;	// L2585
      cand2 = v1647;	// L2586
      ap_int<26> v1648 = cand2;	// L2587
      bool v1649;
      ap_int<26> v1649_tmp = v1648;
      v1649 = v1649_tmp[25];	// L2588
      int32_t v1650 = v1649;	// L2589
      bool v1651 = v1650 == 0;	// L2590
      if (v1651) {	// L2591
        int32_t v1652 = sp6[0];	// L2592
        ap_int<33> v1653 = v1652;	// L2593
        ap_int<33> v1654 = v1653 + 1;	// L2594
        int32_t v1655 = v1654;	// L2595
        sp6[0] = v1655;	// L2596
      } else {
        int32_t v1656 = dcred6[0];	// L2598
        bool v1657 = v1656 > 0;	// L2599
        if (v1657) {	// L2600
          ap_int<26> v1658 = cand2;	// L2601
          pw2 = v1658;	// L2602
          int32_t v1659 = dcred6[0];	// L2603
          ap_int<33> v1660 = v1659;	// L2604
          ap_int<33> v1661 = v1660 - 1;	// L2605
          int32_t v1662 = v1661;	// L2606
          dcred6[0] = v1662;	// L2607
          int32_t v1663 = sp6[0];	// L2608
          ap_int<33> v1664 = v1663;	// L2609
          ap_int<33> v1665 = v1664 + 1;	// L2610
          int32_t v1666 = v1665;	// L2611
          sp6[0] = v1666;	// L2612
        }
      }
    }
    ap_int<26> v1667 = pw2;	// L2616
    v1619.write(v1667);	// L2617
  }
}

void rdrv_s_0(
  int32_t v1668[1][200],
  hls::stream< ap_uint<26> >& v1669,
  hls::stream< int32_t >& v1670
) {	// L2621
  int32_t dcred7[1];	// L2628
  for (int v1672 = 0; v1672 < 1; v1672++) {	// L2629
    dcred7[v1672] = 0;	// L2629
  }
  int32_t sp7[1];	// L2630
  for (int v1674 = 0; v1674 < 1; v1674++) {	// L2631
    sp7[v1674] = 0;	// L2631
  }
  ap_uint<26> zp3;	// L2632
  zp3 = 0;	// L2633
  ap_int<26> v1676 = zp3;	// L2634
  v1669.write(v1676);	// L2635
  ap_int<26> v1677 = zp3;	// L2636
  v1669.write(v1677);	// L2637
  ap_int<26> v1678 = zp3;	// L2638
  v1669.write(v1678);	// L2639
  ap_int<26> v1679 = zp3;	// L2640
  v1669.write(v1679);	// L2641
  ap_int<26> v1680 = zp3;	// L2642
  v1669.write(v1680);	// L2643
  l_S_t_0_t12: for (int t12 = 0; t12 < 200; t12++) {	// L2644
    int32_t v1682 = v1670.read();	// L2645
    int32_t v1683 = dcred7[0];	// L2646
    ap_int<33> v1684 = v1683;	// L2647
    ap_int<33> v1685 = v1682;	// L2648
    ap_int<33> v1686 = v1684 + v1685;	// L2649
    int32_t v1687 = v1686;	// L2650
    dcred7[0] = v1687;	// L2651
    ap_uint<26> pw3;	// L2652
    pw3 = 0;	// L2653
    int32_t v1689 = sp7[0];	// L2654
    bool v1690 = v1689 < 200;	// L2655
    if (v1690) {	// L2656
      ap_uint<26> cand3;	// L2657
      cand3 = 0;	// L2658
      int32_t v1692 = sp7[0];	// L2659
      int v1693 = v1692;	// L2660
      int32_t v1694 = v1668[0][v1693];	// L2661
      ap_uint<26> v1695 = v1694;	// L2662
      ap_int<26> v1696 = cand3;	// L2663
      ap_int<26> v1697;
      ap_int<26> v1697_tmp = v1696;
      v1697_tmp(25, 0) = v1695;
      v1697 = v1697_tmp;	// L2664
      cand3 = v1697;	// L2665
      ap_int<26> v1698 = cand3;	// L2666
      bool v1699;
      ap_int<26> v1699_tmp = v1698;
      v1699 = v1699_tmp[25];	// L2667
      int32_t v1700 = v1699;	// L2668
      bool v1701 = v1700 == 0;	// L2669
      if (v1701) {	// L2670
        int32_t v1702 = sp7[0];	// L2671
        ap_int<33> v1703 = v1702;	// L2672
        ap_int<33> v1704 = v1703 + 1;	// L2673
        int32_t v1705 = v1704;	// L2674
        sp7[0] = v1705;	// L2675
      } else {
        int32_t v1706 = dcred7[0];	// L2677
        bool v1707 = v1706 > 0;	// L2678
        if (v1707) {	// L2679
          ap_int<26> v1708 = cand3;	// L2680
          pw3 = v1708;	// L2681
          int32_t v1709 = dcred7[0];	// L2682
          ap_int<33> v1710 = v1709;	// L2683
          ap_int<33> v1711 = v1710 - 1;	// L2684
          int32_t v1712 = v1711;	// L2685
          dcred7[0] = v1712;	// L2686
          int32_t v1713 = sp7[0];	// L2687
          ap_int<33> v1714 = v1713;	// L2688
          ap_int<33> v1715 = v1714 + 1;	// L2689
          int32_t v1716 = v1715;	// L2690
          sp7[0] = v1716;	// L2691
        }
      }
    }
    ap_int<26> v1717 = pw3;	// L2695
    v1669.write(v1717);	// L2696
  }
}

void rclc_w_0(
  int32_t v1718[1][200],
  hls::stream< int32_t >& v1719,
  hls::stream< ap_uint<26> >& v1720
) {	// L2700
  int32_t k6[1];	// L2709
  for (int v1722 = 0; v1722 < 1; v1722++) {	// L2710
    k6[v1722] = 0;	// L2710
  }
  int32_t cret4[1];	// L2711
  for (int v1724 = 0; v1724 < 1; v1724++) {	// L2712
    cret4[v1724] = 0;	// L2712
  }
  int32_t zc4;	// L2713
  zc4 = 0;	// L2714
  int32_t v1726 = zc4;	// L2715
  v1719.write(v1726);	// L2716
  int32_t v1727 = zc4;	// L2717
  v1719.write(v1727);	// L2718
  int32_t v1728 = zc4;	// L2719
  v1719.write(v1728);	// L2720
  int32_t v1729 = zc4;	// L2721
  v1719.write(v1729);	// L2722
  int32_t v1730 = zc4;	// L2723
  v1719.write(v1730);	// L2724
  cret4[0] = 2;	// L2725
  int32_t v1731 = cret4[0];	// L2726
  v1719.write(v1731);	// L2727
  l_S_t_0_t13: for (int t13 = 0; t13 < 200; t13++) {	// L2728
    ap_uint<26> v1733 = v1720.read();	// L2729
    ap_uint<26> pw4;	// L2730
    pw4 = v1733;	// L2731
    cret4[0] = 0;	// L2732
    ap_int<26> v1735 = pw4;	// L2733
    bool v1736;
    ap_int<26> v1736_tmp = v1735;
    v1736 = v1736_tmp[25];	// L2734
    int32_t v1737 = v1736;	// L2735
    bool v1738 = v1737 == 1;	// L2736
    if (v1738) {	// L2737
      cret4[0] = 1;	// L2738
      int32_t v1739 = k6[0];	// L2739
      bool v1740 = v1739 < 200;	// L2740
      if (v1740) {	// L2741
        ap_int<26> v1741 = pw4;	// L2742
        int32_t v1742 = v1741;	// L2743
        int32_t v1743 = v1742 & 67108863;	// L2744
        int32_t v1744 = k6[0];	// L2745
        int v1745 = v1744;	// L2746
        v1718[0][v1745] = v1743;	// L2747
        int32_t v1746 = k6[0];	// L2748
        ap_int<33> v1747 = v1746;	// L2749
        ap_int<33> v1748 = v1747 + 1;	// L2750
        int32_t v1749 = v1748;	// L2751
        k6[0] = v1749;	// L2752
      }
    }
    int32_t v1750 = cret4[0];	// L2755
    v1719.write(v1750);	// L2756
  }
}

void rclc_e_0(
  int32_t v1751[1][200],
  hls::stream< int32_t >& v1752,
  hls::stream< ap_uint<26> >& v1753
) {	// L2760
  int32_t k7[1];	// L2769
  for (int v1755 = 0; v1755 < 1; v1755++) {	// L2770
    k7[v1755] = 0;	// L2770
  }
  int32_t cret5[1];	// L2771
  for (int v1757 = 0; v1757 < 1; v1757++) {	// L2772
    cret5[v1757] = 0;	// L2772
  }
  int32_t zc5;	// L2773
  zc5 = 0;	// L2774
  int32_t v1759 = zc5;	// L2775
  v1752.write(v1759);	// L2776
  int32_t v1760 = zc5;	// L2777
  v1752.write(v1760);	// L2778
  int32_t v1761 = zc5;	// L2779
  v1752.write(v1761);	// L2780
  int32_t v1762 = zc5;	// L2781
  v1752.write(v1762);	// L2782
  int32_t v1763 = zc5;	// L2783
  v1752.write(v1763);	// L2784
  cret5[0] = 2;	// L2785
  int32_t v1764 = cret5[0];	// L2786
  v1752.write(v1764);	// L2787
  l_S_t_0_t14: for (int t14 = 0; t14 < 200; t14++) {	// L2788
    ap_uint<26> v1766 = v1753.read();	// L2789
    ap_uint<26> pw5;	// L2790
    pw5 = v1766;	// L2791
    cret5[0] = 0;	// L2792
    ap_int<26> v1768 = pw5;	// L2793
    bool v1769;
    ap_int<26> v1769_tmp = v1768;
    v1769 = v1769_tmp[25];	// L2794
    int32_t v1770 = v1769;	// L2795
    bool v1771 = v1770 == 1;	// L2796
    if (v1771) {	// L2797
      cret5[0] = 1;	// L2798
      int32_t v1772 = k7[0];	// L2799
      bool v1773 = v1772 < 200;	// L2800
      if (v1773) {	// L2801
        ap_int<26> v1774 = pw5;	// L2802
        int32_t v1775 = v1774;	// L2803
        int32_t v1776 = v1775 & 67108863;	// L2804
        int32_t v1777 = k7[0];	// L2805
        int v1778 = v1777;	// L2806
        v1751[0][v1778] = v1776;	// L2807
        int32_t v1779 = k7[0];	// L2808
        ap_int<33> v1780 = v1779;	// L2809
        ap_int<33> v1781 = v1780 + 1;	// L2810
        int32_t v1782 = v1781;	// L2811
        k7[0] = v1782;	// L2812
      }
    }
    int32_t v1783 = cret5[0];	// L2815
    v1752.write(v1783);	// L2816
  }
}

void rclc_n_0(
  int32_t v1784[1][200],
  hls::stream< int32_t >& v1785,
  hls::stream< ap_uint<26> >& v1786
) {	// L2820
  int32_t k8[1];	// L2829
  for (int v1788 = 0; v1788 < 1; v1788++) {	// L2830
    k8[v1788] = 0;	// L2830
  }
  int32_t cret6[1];	// L2831
  for (int v1790 = 0; v1790 < 1; v1790++) {	// L2832
    cret6[v1790] = 0;	// L2832
  }
  int32_t zc6;	// L2833
  zc6 = 0;	// L2834
  int32_t v1792 = zc6;	// L2835
  v1785.write(v1792);	// L2836
  int32_t v1793 = zc6;	// L2837
  v1785.write(v1793);	// L2838
  int32_t v1794 = zc6;	// L2839
  v1785.write(v1794);	// L2840
  int32_t v1795 = zc6;	// L2841
  v1785.write(v1795);	// L2842
  int32_t v1796 = zc6;	// L2843
  v1785.write(v1796);	// L2844
  cret6[0] = 2;	// L2845
  int32_t v1797 = cret6[0];	// L2846
  v1785.write(v1797);	// L2847
  l_S_t_0_t15: for (int t15 = 0; t15 < 200; t15++) {	// L2848
    ap_uint<26> v1799 = v1786.read();	// L2849
    ap_uint<26> pw6;	// L2850
    pw6 = v1799;	// L2851
    cret6[0] = 0;	// L2852
    ap_int<26> v1801 = pw6;	// L2853
    bool v1802;
    ap_int<26> v1802_tmp = v1801;
    v1802 = v1802_tmp[25];	// L2854
    int32_t v1803 = v1802;	// L2855
    bool v1804 = v1803 == 1;	// L2856
    if (v1804) {	// L2857
      cret6[0] = 1;	// L2858
      int32_t v1805 = k8[0];	// L2859
      bool v1806 = v1805 < 200;	// L2860
      if (v1806) {	// L2861
        ap_int<26> v1807 = pw6;	// L2862
        int32_t v1808 = v1807;	// L2863
        int32_t v1809 = v1808 & 67108863;	// L2864
        int32_t v1810 = k8[0];	// L2865
        int v1811 = v1810;	// L2866
        v1784[0][v1811] = v1809;	// L2867
        int32_t v1812 = k8[0];	// L2868
        ap_int<33> v1813 = v1812;	// L2869
        ap_int<33> v1814 = v1813 + 1;	// L2870
        int32_t v1815 = v1814;	// L2871
        k8[0] = v1815;	// L2872
      }
    }
    int32_t v1816 = cret6[0];	// L2875
    v1785.write(v1816);	// L2876
  }
}

void rclc_s_0(
  int32_t v1817[1][200],
  hls::stream< int32_t >& v1818,
  hls::stream< ap_uint<26> >& v1819
) {	// L2880
  int32_t k9[1];	// L2889
  for (int v1821 = 0; v1821 < 1; v1821++) {	// L2890
    k9[v1821] = 0;	// L2890
  }
  int32_t cret7[1];	// L2891
  for (int v1823 = 0; v1823 < 1; v1823++) {	// L2892
    cret7[v1823] = 0;	// L2892
  }
  int32_t zc7;	// L2893
  zc7 = 0;	// L2894
  int32_t v1825 = zc7;	// L2895
  v1818.write(v1825);	// L2896
  int32_t v1826 = zc7;	// L2897
  v1818.write(v1826);	// L2898
  int32_t v1827 = zc7;	// L2899
  v1818.write(v1827);	// L2900
  int32_t v1828 = zc7;	// L2901
  v1818.write(v1828);	// L2902
  int32_t v1829 = zc7;	// L2903
  v1818.write(v1829);	// L2904
  cret7[0] = 2;	// L2905
  int32_t v1830 = cret7[0];	// L2906
  v1818.write(v1830);	// L2907
  l_S_t_0_t16: for (int t16 = 0; t16 < 200; t16++) {	// L2908
    ap_uint<26> v1832 = v1819.read();	// L2909
    ap_uint<26> pw7;	// L2910
    pw7 = v1832;	// L2911
    cret7[0] = 0;	// L2912
    ap_int<26> v1834 = pw7;	// L2913
    bool v1835;
    ap_int<26> v1835_tmp = v1834;
    v1835 = v1835_tmp[25];	// L2914
    int32_t v1836 = v1835;	// L2915
    bool v1837 = v1836 == 1;	// L2916
    if (v1837) {	// L2917
      cret7[0] = 1;	// L2918
      int32_t v1838 = k9[0];	// L2919
      bool v1839 = v1838 < 200;	// L2920
      if (v1839) {	// L2921
        ap_int<26> v1840 = pw7;	// L2922
        int32_t v1841 = v1840;	// L2923
        int32_t v1842 = v1841 & 67108863;	// L2924
        int32_t v1843 = k9[0];	// L2925
        int v1844 = v1843;	// L2926
        v1817[0][v1844] = v1842;	// L2927
        int32_t v1845 = k9[0];	// L2928
        ap_int<33> v1846 = v1845;	// L2929
        ap_int<33> v1847 = v1846 + 1;	// L2930
        int32_t v1848 = v1847;	// L2931
        k9[0] = v1848;	// L2932
      }
    }
    int32_t v1849 = cret7[0];	// L2935
    v1818.write(v1849);	// L2936
  }
}

/// This is top function.
void top(
  half v1850[1][200],
  int32_t v1851[1][200],
  half v1852[1][200],
  int32_t v1853[1][200],
  half v1854[1][200],
  int32_t v1855[1][200],
  half v1856[1][200],
  int32_t v1857[1][200],
  half v1858[1][200],
  half v1859[1][200],
  half v1860[1][200],
  half v1861[1][200],
  int32_t v1862[1][200],
  int32_t v1863[1][200],
  int32_t v1864[1][200],
  int32_t v1865[1][200],
  int32_t v1866[1][200],
  int32_t v1867[1][200],
  int32_t v1868[1][200],
  int32_t v1869[1][200]
) {	// L2940
  #pragma HLS dataflow
  hls::stream< ap_uint<17> > v1870;
  #pragma HLS stream variable=v1870 depth=8	// L2941
  hls::stream< ap_uint<17> > v1871;
  #pragma HLS stream variable=v1871 depth=8	// L2942
  hls::stream< ap_uint<17> > v1872;
  #pragma HLS stream variable=v1872 depth=8	// L2943
  hls::stream< ap_uint<17> > v1873;
  #pragma HLS stream variable=v1873 depth=8	// L2944
  hls::stream< ap_uint<17> > v1874;
  #pragma HLS stream variable=v1874 depth=8	// L2945
  hls::stream< ap_uint<17> > v1875;
  #pragma HLS stream variable=v1875 depth=8	// L2946
  hls::stream< ap_uint<17> > v1876;
  #pragma HLS stream variable=v1876 depth=8	// L2947
  hls::stream< ap_uint<17> > v1877;
  #pragma HLS stream variable=v1877 depth=8	// L2948
  hls::stream< ap_uint<26> > v1878;
  #pragma HLS stream variable=v1878 depth=8	// L2949
  hls::stream< ap_uint<26> > v1879;
  #pragma HLS stream variable=v1879 depth=8	// L2950
  hls::stream< ap_uint<26> > v1880;
  #pragma HLS stream variable=v1880 depth=8	// L2951
  hls::stream< ap_uint<26> > v1881;
  #pragma HLS stream variable=v1881 depth=8	// L2952
  hls::stream< ap_uint<26> > v1882;
  #pragma HLS stream variable=v1882 depth=8	// L2953
  hls::stream< ap_uint<26> > v1883;
  #pragma HLS stream variable=v1883 depth=8	// L2954
  hls::stream< ap_uint<26> > v1884;
  #pragma HLS stream variable=v1884 depth=8	// L2955
  hls::stream< ap_uint<26> > v1885;
  #pragma HLS stream variable=v1885 depth=8	// L2956
  hls::stream< int32_t > v1886;
  #pragma HLS stream variable=v1886 depth=8	// L2957
  hls::stream< int32_t > v1887;
  #pragma HLS stream variable=v1887 depth=8	// L2958
  hls::stream< int32_t > v1888;
  #pragma HLS stream variable=v1888 depth=8	// L2959
  hls::stream< int32_t > v1889;
  #pragma HLS stream variable=v1889 depth=8	// L2960
  hls::stream< int32_t > v1890;
  #pragma HLS stream variable=v1890 depth=8	// L2961
  hls::stream< int32_t > v1891;
  #pragma HLS stream variable=v1891 depth=8	// L2962
  hls::stream< int32_t > v1892;
  #pragma HLS stream variable=v1892 depth=8	// L2963
  hls::stream< int32_t > v1893;
  #pragma HLS stream variable=v1893 depth=8	// L2964
  hls::stream< int32_t > v1894;
  #pragma HLS stream variable=v1894 depth=8	// L2965
  hls::stream< int32_t > v1895;
  #pragma HLS stream variable=v1895 depth=8	// L2966
  hls::stream< int32_t > v1896;
  #pragma HLS stream variable=v1896 depth=8	// L2967
  hls::stream< int32_t > v1897;
  #pragma HLS stream variable=v1897 depth=8	// L2968
  hls::stream< int32_t > v1898;
  #pragma HLS stream variable=v1898 depth=8	// L2969
  hls::stream< int32_t > v1899;
  #pragma HLS stream variable=v1899 depth=8	// L2970
  hls::stream< int32_t > v1900;
  #pragma HLS stream variable=v1900 depth=8	// L2971
  hls::stream< int32_t > v1901;
  #pragma HLS stream variable=v1901 depth=8	// L2972
  node_0_0(v1879, v1880, v1883, v1884, v1871, v1872, v1875, v1876, v1886, v1889, v1890, v1893, v1894, v1897, v1898, v1901, v1878, v1881, v1882, v1885, v1887, v1888, v1891, v1892, v1900, v1899, v1896, v1895, v1870, v1873, v1874, v1877);	// L2973
  drv_w_0(v1850, v1851, v1870, v1894);	// L2974
  drv_e_0(v1852, v1853, v1873, v1897);	// L2975
  drv_n_0(v1854, v1855, v1874, v1898);	// L2976
  drv_s_0(v1856, v1857, v1877, v1901);	// L2977
  col_w_0(v1858, v1896, v1872);	// L2978
  col_e_0(v1859, v1895, v1871);	// L2979
  col_n_0(v1860, v1900, v1876);	// L2980
  col_s_0(v1861, v1899, v1875);	// L2981
  rdrv_w_0(v1862, v1878, v1886);	// L2982
  rdrv_e_0(v1863, v1881, v1889);	// L2983
  rdrv_n_0(v1864, v1882, v1890);	// L2984
  rdrv_s_0(v1865, v1885, v1893);	// L2985
  rclc_w_0(v1866, v1888, v1880);	// L2986
  rclc_e_0(v1867, v1887, v1879);	// L2987
  rclc_n_0(v1868, v1892, v1884);	// L2988
  rclc_s_0(v1869, v1891, v1883);	// L2989
}

